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

public:
	void InputMove(const FVector& Direction, float Scale);
	void InputRunning(bool IsRun);
	void InputStealthToggle();
	void InputSpeedControl();
	void InputAttack();

	UFUNCTION()
	void OnSectionJumpReady(class USectionControlNotify* SectionControl);

	UFUNCTION()
	void OnSectionJumpEnd(class USectionControlNotify* SectionControl);

protected:
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UQuestComponent* QuestComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	MoveState PlayerMoveState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float NormalMoveSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float RunningMoveSpeed = 900.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharaterOption")
	float StealthMoveSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerMovement")
	UAnimMontage* AttackMontage = nullptr;

private:
	bool bStealthToggle = false;

	class USectionControlNotify* SectionNotify = nullptr;
	bool bEnableControlNotify = false;
};
