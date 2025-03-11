// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject_Base.h"
#include "../Framework/PlayerCharacterController.h"

// Sets default values
AInteractObject_Base::AInteractObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	SetRootComponent(RootComponent);

	InteractArea = CreateDefaultSubobject<USphereComponent>(FName("InteractArea"));
	InteractArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractObject_Base::BeginPlay()
{
	Super::BeginPlay();

	TArray<UItemData*> itemDatas = UItemDataManager::GetInstance()->GetItemDataList();
	for (const TPair<int, int>& Pair : ContainerIndex) {
		ContainerInventory.Add(FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], Pair.Value));
	}

	bIsInit = false;
}

// Called every frame
void AInteractObject_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractObject_Base::SetContainerUI()
{
	APlayerCharacterController* Controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	Controller->InventoryUI->Widget_Container->ResetContainer();
	if (!bIsInit) {
		bIsInit = true;
		for (int i = 0; i < ContainerInventory.Num(); i++) {
			FInventoryData& itemData = ContainerInventory[i];
			itemData.SlotIndex = Controller->InventoryUI->Widget_Container->MakeItemToSlot(itemData.ItemData, itemData.ItemCount);
		}
	}
	else {
		Controller->InventoryUI->Widget_Container->ShowContainer(ContainerInventory);
	}
}

