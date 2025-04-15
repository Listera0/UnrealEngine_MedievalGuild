// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "../Object/IInteractInterface.h"
#include "../UI/PlayerInventory.h"
#include "Enemy_1.generated.h"

UCLASS()
class MEDIEVALGUILD_API AEnemy_1 : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	AEnemy_1();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetInteractDistance(float distance) override { InteractDistance = distance; };
	virtual float GetInteractDistance() override { return InteractDistance; };

	FVector GetNextPatrolLocation();
	void InventoryInitSetting();
	void SetContainerUI();
	void RecieveHit(float Damage);
	void Die();
	void AttackAction();
	bool CheckAttackAnim();

	UPROPERTY(EditAnywhere, Category = "Enemy|Location")
	FName EnemyLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Weapon")
	UStaticMeshComponent* EnemyWeapon = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Weapon")
	UCapsuleComponent* EnemyWeaponCollision = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy|Anim")
	UAnimMontage* DeathMontage = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy|Anim")
	UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|Inventory")
	TMap<int, int> EnemyInventoryInit;
	TArray<FInventoryData*> EnemyInventory;
	TArray<AActor*> AlreadyHitActor;
	class AStageActor* EnemyLocationStage;

	UPROPERTY(EditAnywhere, Category = "Enemy|Weapon")
	int WeaponIndex = 12;
	int CurrentPatrolLocation;
	bool bIsInit = false;
	float MaxHealth = 100.0f;
	float CurrentHealth = 0.0f;
	float InteractDistance;
};
