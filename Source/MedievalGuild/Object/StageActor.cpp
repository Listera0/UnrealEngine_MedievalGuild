// Fill out your copyright notice in the Description page of Project Settings.


#include "StageActor.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/DebugManager.h"
#include "../Item/ItemDataManager.h"
#include "../DataAssets/ItemDropDataAsset.h"

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

	InteractContainerOwner = CreateDefaultSubobject<USceneComponent>(FName("InteractContainerOwner"));
	InteractContainerOwner->SetupAttachment(RootComponent);

	ExtractAreaOwner = CreateDefaultSubobject<USceneComponent>(FName("ExtractAreaOwner"));
	ExtractAreaOwner->SetupAttachment(RootComponent);

	EnemySpawnOwner = CreateDefaultSubobject<USceneComponent>(FName("EnemySpawnOwner"));
	EnemySpawnOwner->SetupAttachment(RootComponent);

	EnemyPatrolOwner = CreateDefaultSubobject<USceneComponent>(FName("EnemyPatrolOwner"));
	EnemyPatrolOwner->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<AEnemy_1> EnemyClassFinder(TEXT("/Game/CPP/Character/BP_Enemy_Base.BP_Enemy_Base_C"));
	EnemyClass = EnemyClassFinder.Class;
}

// Called when the game starts or when spawned
void AStageActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	InitStageActor();
}

void AStageActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player")) {
		extractTimer = 0.0f;
		PlayerController->ScreenUI->SetExtractText(false, 0.0f);
		InteractActor = OtherActor;
		bIsInteractExtractionArea = true;
	}
}

void AStageActor::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player")) {
		extractTimer = 0.0f;
		PlayerController->ScreenUI->SetExtractText(false, 0.0f);
		InteractActor = nullptr;
		bIsInteractExtractionArea = false;
	}
}

// Called every frame
void AStageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float extractNeed = 2.0f;

	if (bIsInteractExtractionArea && InteractActor && !InteractActor->ActorHasTag("Dead")) {
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

int AStageActor::GetRandomPatrolLocation(int ignore)
{
	int returnValue = FMath::RandRange(0, EnemyPatrolOwner->GetAttachChildren().Num() - 1);

	if (returnValue == ignore) return GetRandomPatrolLocation(ignore);

	return returnValue;
}

FVector AStageActor::GetPatrolLocationVector(int index)
{
	return GetActorLocation() + EnemyPatrolOwner->GetAttachChildren()[index]->GetRelativeLocation();
}

void AStageActor::InitStageActor()
{
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

	for (USceneComponent* child : ExtractAreaOwner->GetAttachChildren()) {
		UBoxComponent* extractArea = Cast<UBoxComponent>(child);
		extractArea->OnComponentBeginOverlap.AddDynamic(this, &AStageActor::OnBoxOverlapBegin);
		extractArea->OnComponentEndOverlap.AddDynamic(this, &AStageActor::OnBoxOverlapEnd);
	}
}

void AStageActor::ResetStageActor()
{
	for (AInteractObject_Base* items : SpawnedItems) { if (items) items->Destroy(); }
	for (AInteractObject_Base* containers : SpawnedContainers) { if (containers) containers->Destroy(); }
	for (AEnemy_1* enemys : SpawnedEnemys) { if (enemys) enemys->Destroy(); }

	SpawnedItems.Empty();
	SpawnedContainers.Empty();
	SpawnedEnemys.Empty();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (USceneComponent* spawnPoint : SpawnPoints) {
		FStringAssetReference spawnRef(FString::Printf(TEXT("/Game/CPP/DataAsset/%d_DropData"), 0));
		UItemDropDataAsset* dropData = Cast<UItemDropDataAsset>(spawnRef.TryLoad());

		int targetItemIndex = 0;
		int totalValue = 0; for (const TPair<int, int>& Pair : dropData->DropItemInfo) { totalValue += Pair.Value; }
		int randValue = FMath::RandRange(1, totalValue); int currentValue = 0;

		for (const TPair<int, int>& Pair : dropData->DropItemInfo) {
			currentValue += Pair.Value;
			if (randValue <= currentValue) {
				targetItemIndex = Pair.Key;
				break;
			}
		}

		UItemData* itemData = UItemDataManager::GetInstance()->GetItemDataList()[targetItemIndex];

		AInteractObject_Base* newItem = GetWorld()->SpawnActor<AInteractObject_Base>(AInteractObject_Base::StaticClass(),
			GetActorLocation() + spawnPoint->GetRelativeLocation(), spawnPoint->GetRelativeRotation(), SpawnParameters);

		newItem->Tags = TArray<FName>{ FName("Interactable"), FName("Item") };
		newItem->ContainerInventory.Add(new FInventoryData(FVector2D(-1.0f), itemData, 1));
		newItem->InteractableItemSetting();
		SpawnedItems.Add(newItem);
	}

	for (USceneComponent* spawnPoint : EnemySpawnOwner->GetAttachChildren()) {
		AEnemy_1* newEnemy = GetWorld()->SpawnActor<AEnemy_1>(EnemyClass, GetActorLocation() + spawnPoint->GetRelativeLocation(), spawnPoint->GetRelativeRotation(), SpawnParameters);
		newEnemy->EnemyLocation = LocationName;
		newEnemy->WeaponIndex = 12;
		SpawnedEnemys.Add(newEnemy);
	}

	for (USceneComponent* spawnPoint : InteractContainerOwner->GetAttachChildren()) {
		AInteractObject_Base* newItem = GetWorld()->SpawnActor<AInteractObject_Base>(AInteractObject_Base::StaticClass(),
			GetActorLocation() + spawnPoint->GetRelativeLocation(), spawnPoint->GetRelativeRotation(), SpawnParameters);
		newItem->Tags = TArray<FName>{ FName("Interactable"), FName("Container") };
		newItem->bFollowDataSet = true;
		newItem->DataSetIndex = 0;
		newItem->InteractableItemSetting();
		SpawnedContainers.Add(newItem);
	}
}

