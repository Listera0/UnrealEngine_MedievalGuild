// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject_Base.h"
#include "../Framework/PlayerCharacterController.h"
#include "../DataAssets/ItemScaleDataAsset.h"
#include "UObject/ConstructorHelpers.h"
#include "../DataAssets/ItemContainerDataAsset.h"

// Sets default values
AInteractObject_Base::AInteractObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	SetRootComponent(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractObject_Base::BeginPlay()
{
	Super::BeginPlay();

	InteractableItemSetting();
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

// Called every frame
void AInteractObject_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractObject_Base::SetContainerUI()
{
	APlayerCharacterController* Controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	EContainerCategory targetCategory = EContainerCategory::None;

	if (Controller->InteractObj->ActorHasTag("Container")) { targetCategory = EContainerCategory::Container; }
	else if (Controller->InteractObj->ActorHasTag("Merchant")) { targetCategory = EContainerCategory::Merchant; }
	else if (Controller->InteractObj->ActorHasTag("Anvil")) { targetCategory = EContainerCategory::CraftInventory; }

	UContainer_Base* targetContainerPanel = Controller->GetTargetContainer(targetCategory);

	targetContainerPanel->ResetContainer();
	if (!bIsInit) {
		bIsInit = true;
		for (int i = 0; i < ContainerInventory.Num(); i++) {
			FInventoryData* itemData = ContainerInventory[i];
			itemData->SlotIndex = targetContainerPanel->MakeItem(itemData);
		}
	}
	targetContainerPanel->ShowContainer(ContainerInventory);
}

void AInteractObject_Base::InteractableItemSetting()
{
	bIsInit = false;

	TArray<UItemData*> itemDatas = UItemDataManager::GetInstance()->GetItemDataList();
	if (bFollowDataSet) {
		FStringAssetReference spawnRef(FString::Printf(TEXT("/Game/CPP/DataAsset/%d_ContainerData"), DataSetIndex));
		UItemContainerDataAsset* containerData = Cast<UItemContainerDataAsset>(spawnRef.TryLoad());

		for (const TPair<int, int>& Pair : containerData->ItemInfo) {
			if (FMath::RandRange(1, 100) <= Pair.Value) {
				int count = FMath::RandRange(*containerData->ItemMinCount.Find(Pair.Key), *containerData->ItemMaxCount.Find(Pair.Key));
				ContainerInventory.Add(new FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], count));
			}
		}
	}
	else {
		for (const TPair<int, int>& Pair : ContainerIndex) {
			ContainerInventory.Add(new FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], Pair.Value));
		}
	}

	if (ActorHasTag("Item")) {
		if (UItemDataManager::GetInstance()->GetMeshForItem(ContainerInventory[0]->ItemData) != nullptr) {
			StaticMesh->SetStaticMesh(UItemDataManager::GetInstance()->GetMeshForItem(ContainerInventory[0]->ItemData));
			StaticMesh->SetMaterial(0, UItemDataManager::GetInstance()->GetMaterialForItem(ContainerInventory[0]->ItemData));
		}

		FStringAssetReference AssetRef(FString::Printf(TEXT("/Game/CPP/DataAsset/%d_ScaleData"), ContainerInventory[0]->ItemData->index));
		UItemScaleDataAsset* ItemDataAsset = Cast<UItemScaleDataAsset>(AssetRef.TryLoad());
		if (ItemDataAsset) {
			StaticMesh->SetRelativeScale3D(FVector(ItemDataAsset->Scale, ItemDataAsset->Scale, ItemDataAsset->Scale));
			StaticMesh->SetRelativeRotation(ItemDataAsset->Rotation);
		}

		StaticMesh->SetSimulatePhysics(true);
		StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
	}
	else if (ActorHasTag("Container")) {
		FStringAssetReference AssetRef(FString::Printf(TEXT("/Game/Asset/Items/Chest_Combine")));
		UStaticMesh* itemStaticMesh = Cast<UStaticMesh>(AssetRef.TryLoad());
		if (itemStaticMesh) { 
			StaticMesh->SetStaticMesh(itemStaticMesh); 
			StaticMesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	}
}

void AInteractObject_Base::AddItemToInv(FInventoryData* data)
{

	// 자리가 고정이 아님
	if (data->SlotIndex == FVector2D(-1.0f)) {
		FInventoryData* targetData = HasItem(data->ItemData->index, true);
		if (targetData) {
			int value = targetData->ItemData->maxStack - targetData->ItemCount;
			if (value < data->ItemCount) {
				targetData->ItemCount = targetData->ItemData->maxStack;
				data->ItemCount -= value;
				AddItemToInv(data);
			}
			else {
				targetData->ItemCount += data->ItemCount;
			}
		}
		else {
			ContainerInventory.Add(data);
			bIsInit = false;
		}
	}
	else { // 자리가 고정
		// 해당 위치에 아이템이 같은 종류일때
		FInventoryData* targetData = FindItemWithLocation(data->SlotIndex);
		if (targetData) {
			if (targetData->ItemData->index == data->ItemData->index) {
				int value = targetData->ItemData->maxStack - targetData->ItemCount;
				if (value < data->ItemCount) {
					targetData->ItemCount = targetData->ItemData->maxStack;
					data->ItemCount -= value;
					data->SlotIndex = FVector2D(-1.0f);
					AddItemToInv(data);
				}
				else {
					targetData->ItemCount += data->ItemCount;
				}
			}
		}
		else {
			ContainerInventory.Add(data);
			bIsInit = false;
		}
	}
}

void AInteractObject_Base::RemoveItemToInv(FVector2D location, int count, bool withDelete)
{
	FInventoryData* targetData = FindItemWithLocation(location);
	if (targetData) {
		if (targetData->ItemCount < count) {
			ContainerInventory.Remove(targetData);
			if(withDelete) delete targetData;
		}
		else {
			if ((targetData->ItemCount -= count) <= 0) {
				ContainerInventory.Remove(targetData);
				if (withDelete) delete targetData;
			}
		}
	}
}

void AInteractObject_Base::RemoveItemToInv(UItemData* item, int count, bool withDelete)
{
	FInventoryData* targetData = HasItem(item->index, false);
	if (targetData) {
		if (targetData->ItemCount < count) {
			int tempCount = count - targetData->ItemCount;
			ContainerInventory.Remove(targetData);
			if (withDelete) delete targetData;
			RemoveItemToInv(item, tempCount, withDelete);
		}
		else {
			if ((targetData->ItemCount -= count) <= 0) {
				ContainerInventory.Remove(targetData);
				if (withDelete) delete targetData;
			}
		}
	}
}

void AInteractObject_Base::MoveItemIndex(FVector2D to, FInventoryData* data)
{
	data->SlotIndex = to;
	ContainerInventory.Add(data);
}

void AInteractObject_Base::MoveItemIndex(FVector2D from, FVector2D to)
{
	FInventoryData* targetData = FindItemWithLocation(from);
	if (targetData) {
		targetData->SlotIndex = to;
	}
}


FInventoryData* AInteractObject_Base::HasItem(int itemIndex, bool checkMaxStack)
{
	for (FInventoryData* data : ContainerInventory) {
		if (data->ItemData->index == itemIndex) {
			if (checkMaxStack) {
				if (data->ItemCount < data->ItemData->maxStack) {
					return data;
				}
			}
			else {
				return data;
			}
		}
	}

	return nullptr;
}

FInventoryData* AInteractObject_Base::FindItemWithLocation(FVector2D location)
{
	for (FInventoryData* data : ContainerInventory) {
		if (data->SlotIndex == location) {
			return data;
		}
	}

	return nullptr;
}

