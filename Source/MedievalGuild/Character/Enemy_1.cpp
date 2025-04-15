// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_1.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"
#include "../DataAssets/WeaponTransformDataAsset.h"
#include "../DataAssets/ItemContainerDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "../Object/StageActor.h"

AEnemy_1::AEnemy_1()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon"));
	EnemyWeapon->SetupAttachment(GetMesh());

	EnemyWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCollision"));
	EnemyWeaponCollision->SetupAttachment(EnemyWeapon);
}

// Called when the game starts or when spawned
void AEnemy_1::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference weaponRef(FString::Printf(TEXT("/Game/CPP/DataAsset/WeaponData_%d"), WeaponIndex));
	UWeaponTransformDataAsset* weaponData = Cast<UWeaponTransformDataAsset>(weaponRef.TryLoad());

	InventoryInitSetting();
	CurrentHealth = MaxHealth;

	EnemyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightHand_Socket"));
	EnemyWeapon->SetStaticMesh(weaponData->mesh);
	EnemyWeapon->SetRelativeTransform(weaponData->transfrom);
	EnemyWeapon->SetCollisionProfileName(TEXT("NoCollision"));
	EnemyWeaponCollision->SetRelativeTransform(weaponData->collisionTransform);
	EnemyWeaponCollision->SetCapsuleHalfHeight(weaponData->collisionShape);
	EnemyWeaponCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called every frame
void AEnemy_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AEnemy_1::GetNextPatrolLocation()
{
	if (!EnemyLocationStage) {
		TArray<AActor*> findActorList;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AStageActor::StaticClass(), EnemyLocation, findActorList);
		EnemyLocationStage = Cast<AStageActor>(findActorList[0]);
	}
	
	CurrentPatrolLocation = EnemyLocationStage->GetRandomPatrolLocation(CurrentPatrolLocation);
	return EnemyLocationStage->GetPatrolLocationVector(CurrentPatrolLocation);
}

void AEnemy_1::InventoryInitSetting()
{
	TArray<UItemData*> itemDatas = UItemDataManager::GetInstance()->GetItemDataList();

	FStringAssetReference spawnRef(FString::Printf(TEXT("/Game/CPP/DataAsset/%d_ContainerData"), WeaponIndex));
	UItemContainerDataAsset* containerData = Cast<UItemContainerDataAsset>(spawnRef.TryLoad());

	for (const TPair<int, int>& Pair : containerData->ItemInfo) {
		if (FMath::RandRange(1, 100) <= Pair.Value) {
			int count = FMath::RandRange(*containerData->ItemMinCount.Find(Pair.Key), *containerData->ItemMaxCount.Find(Pair.Key));
			EnemyInventory.Add(new FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], count));
		}
	}

	/*for (const TPair<int, int>& Pair : EnemyInventoryInit) {
		EnemyInventory.Add(new FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], Pair.Value));
	}*/
}

void AEnemy_1::SetContainerUI()
{
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	EContainerCategory targetCategory = EContainerCategory::EnemyInventory;
	UContainer_Base* targetContainerPanel = PlayerController->GetTargetContainer(targetCategory);

	targetContainerPanel->ResetContainer();
	if (!bIsInit) {
		bIsInit = true;
		for (int i = 0; i < EnemyInventory.Num(); i++) {
			FInventoryData* itemData = EnemyInventory[i];
			itemData->SlotIndex = targetContainerPanel->MakeItem(itemData);
		}
	}

	PlayerController->InventoryUI->Widget_EnemyContainer->ShowContainer(EnemyInventory);
}

void AEnemy_1::RecieveHit(float Damage)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.0f) { Die(); }
}

void AEnemy_1::Die()
{
	FTimerHandle timer;
	AController* controller = GetController();
	if (controller) { controller->Destroy(); }
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
	GetWorld()->GetTimerManager().SetTimer(timer, [this]()
	{
		Tags.Add("Dead");
		Tags.Add("Interactable");
		GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
		GetMesh()->bNoSkeletonUpdate = true;
		GetMesh()->bPauseAnims = true;
		EnemyWeapon->SetStaticMesh(nullptr);
		EnemyWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));
	}, DeathMontage->GetPlayLength() - 0.25f, false);
}