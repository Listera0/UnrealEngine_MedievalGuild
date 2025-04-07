// Fill out your copyright notice in the Description page of Project Settings.


#include "StageActor.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"
#include "../Object/InteractObject_Base.h"

// Sets default values
AStageActor::AStageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponents = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	RootComponent = RootComponents;

	SpawnPointOwner = CreateDefaultSubobject<USceneComponent>(FName("SpawnPointOwner"));
	SpawnPointOwner->SetupAttachment(RootComponent);

	SpawnAreaOwner = CreateDefaultSubobject<USceneComponent>(FName("SpawnAreaOnwer"));
	SpawnAreaOwner->SetupAttachment(RootComponent);

	ExtractAreaOwner = CreateDefaultSubobject<USceneComponent>(FName("ExtractAreaOwner"));
	ExtractAreaOwner->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStageActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FStringAssetReference AssetRef("/Game/Asset/Object/UnVissibleMaterial");
	UMaterialInterface* UnVisibleMat = Cast<UMaterialInterface>(AssetRef.TryLoad());

	SpawnPoints = SpawnPointOwner->GetAttachChildren();
	TArray<UStaticMeshComponent*> SpawnAreas;

	for (USceneComponent* child : SpawnAreaOwner->GetAttachChildren())
	{
		UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(child);
		if (StaticMeshComp) { SpawnAreas.Add(StaticMeshComp); }
	}

	for (UStaticMeshComponent* spawnArea : SpawnAreas) {
		if (UnVisibleMat) {
			spawnArea->SetMaterial(0, UnVisibleMat);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("Count %d"), SpawnAreas.Num()));
		}
	}

	for (USceneComponent* spawnPoint : SpawnPoints) {
		UItemData* itemData = UItemDataManager::GetInstance()->GetItemDataList()[0];

		AInteractObject_Base* newItem = GetWorld()->SpawnActor<AInteractObject_Base>(AInteractObject_Base::StaticClass(),
			GetActorLocation() + spawnPoint->GetRelativeLocation(), spawnPoint->GetRelativeRotation(), SpawnParameters);

		newItem->Tags = TArray<FName>{ FName("Interactable"), FName("Item") };
		newItem->ContainerInventory.Add(new FInventoryData(FVector2D(-1.0f), itemData, 1));
		newItem->InteractableItemSetting();
	}

	for (USceneComponent* child : ExtractAreaOwner->GetAttachChildren()) {
		UBoxComponent* extractArea = Cast<UBoxComponent>(child);
		extractArea->OnComponentBeginOverlap.AddDynamic(this, &AStageActor::OnBoxOverlapBegin);
		extractArea->OnComponentEndOverlap.AddDynamic(this, &AStageActor::OnBoxOverlapEnd);
	}
}

void AStageActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	extractTimer = 0.0f;
	PlayerController->ScreenUI->SetExtractText(false, 0.0f);
	bIsInteractExtractionArea = true;
}

void AStageActor::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	extractTimer = 0.0f;
	PlayerController->ScreenUI->SetExtractText(false, 0.0f);
	bIsInteractExtractionArea = false;
}

// Called every frame
void AStageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float extractNeed = 2.0f;

	if (bIsInteractExtractionArea) {
		extractTimer += DeltaTime;

		PlayerController->ScreenUI->SetExtractText(true, extractNeed - extractTimer);
		if (extractTimer > extractNeed) {
			extractTimer = 0.0f;
			bIsInteractExtractionArea = false;
			PlayerController->ScreenUI->SetExtractText(false, 0.0f);
			PlayerController->InventoryUI->Widget_StageMap->MoveToArea("Hideout");
		}
	}
}

