// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_1.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"
#include "../DataAssets/WeaponTransformDataAsset.h"
#include "../DataAssets/ItemContainerDataAsset.h"
#include "../Object/StageActor.h"

AEnemy_1::AEnemy_1()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("Weapon"));
	EnemyWeapon->SetupAttachment(GetMesh());

	EnemyWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCollision"));
	EnemyWeaponCollision->SetupAttachment(EnemyWeapon);
}

void AEnemy_1::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference weaponRef(FString::Printf(TEXT("/Game/Data/DataAsset/WeaponData_%d"), WeaponIndex));
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
	EnemyWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_1::OnAttackBeginOverlap);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	EnemyWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	EnemyWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AEnemy_1::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckAttackAnim() && AttackAnimCurrentTime() >= 0.5f) {
		if (OtherActor->ActorHasTag("Player") && !AlreadyHitActor.Contains(OtherActor)) {
			AlreadyHitActor.Add(OtherActor);
			APlayerCharacter* hitEnemy = Cast<APlayerCharacter>(OtherActor);
			hitEnemy->RecieveHit(this, 100.0f);
		}
	}
}

void AEnemy_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy_1::EnemyInitSetting()
{
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

	FStringAssetReference spawnRef(FString::Printf(TEXT("/Game/Data/DataAsset/%d_ContainerData"), WeaponIndex));
	UItemContainerDataAsset* containerData = Cast<UItemContainerDataAsset>(spawnRef.TryLoad());

	for (const TPair<int, int>& Pair : containerData->ItemInfo) {
		if (FMath::RandRange(1, 100) <= Pair.Value) {
			int count = FMath::RandRange(*containerData->ItemMinCount.Find(Pair.Key), *containerData->ItemMaxCount.Find(Pair.Key));
			EnemyInventory.Add(new FInventoryData(FVector2D(-1.0f), itemDatas[Pair.Key], count));
		}
	}
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
	bDie = true;
	EnemyWeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));

	AController* controller = GetController();
	if (controller) { controller->Destroy(); }
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);

	FTimerHandle timer;
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

void AEnemy_1::AttackAction()
{
	AlreadyHitActor.Empty();
	PlayAnimMontage(AttackMontage);
}

bool AEnemy_1::CheckAttackAnim()
{
	return GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage);
}

float AEnemy_1::AttackAnimCurrentTime()
{
	return GetMesh()->GetAnimInstance()->Montage_GetPosition(AttackMontage);
}
