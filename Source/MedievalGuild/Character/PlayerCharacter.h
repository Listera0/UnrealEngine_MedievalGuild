// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Framework/PlayerCharacterController.h"
#include "Components/CapsuleComponent.h"
#include "../Quest/QuestComponent.h"

#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class MoveState : uint8 {
	Idle = 0 UMETA(DisplayName = "Idle"),
	Run UMETA(DisplayName = "Run"),
	Stealth UMETA(DisplayName = "Stealth")
};

UCLASS()
class MEDIEVALGUILD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
								AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void InputMove(const FVector& Direction, float Scale);
	void InputRunning(bool IsRun);
	void InputStealthToggle();
	void InputSpeedControl();
	void InputAttack(int index = 0);
	void SetPlayerWeapon(int index);
	bool CheckAttackAnim();
	bool CheckDeathAnim();
	void RecieveHit(AActor* enemy, float damage);

	UFUNCTION()
	void OnSectionJumpReady(class USectionControlNotify* SectionControl);

	UFUNCTION()
	void OnSectionJumpEnd(class USectionControlNotify* SectionControl);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	MoveState PlayerMoveState;
	UPROPERTY(EditDefaultsOnly)
	UQuestComponent* QuestComponent = nullptr;

protected:
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PlayerWeapon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* PlayerWeaponCollsion = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float StealthMoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float NormalMoveSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float RunningMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Anim")
	UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Anim")
	UAnimMontage* AttackMontage2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Anim")
	UAnimMontage* DeathMontage = nullptr;

private:
	class APlayerCharacterController* PlayerController = nullptr;
	class USectionControlNotify* SectionNotify = nullptr;

	TArray<AActor*> AlreadyHitActor;
	bool bStealthToggle = false;
	bool bEnableControlNotify = false;

public:
	bool bHasWeapon = false;
};
