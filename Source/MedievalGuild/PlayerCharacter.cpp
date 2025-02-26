// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SectionControlNotify.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 250.0f);
	SpringArm->ProbeSize = 25.0f;
	SpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::InputMove(const FVector& Direction, float Scale)
{
	AddMovementInput(Direction, Scale);
}

void APlayerCharacter::InputRunning(bool IsRun)
{
	bStealthToggle = false;

	if (IsRun)
		PlayerMoveState = MoveState::Run;
	else
		PlayerMoveState = MoveState::Idle;

	InputSpeedControl();
}

void APlayerCharacter::InputStealthToggle()
{
	if (bStealthToggle) {
		PlayerMoveState = MoveState::Idle;
		bStealthToggle = false;
	}
	else {
		PlayerMoveState = MoveState::Stealth;
		bStealthToggle = true;
	}

	InputSpeedControl();
}

void APlayerCharacter::InputSpeedControl()
{
	if (PlayerMoveState == MoveState::Idle) {
		GetCharacterMovement()->MaxWalkSpeed = NormalMoveSpeed;
	}

	if (PlayerMoveState == MoveState::Run) {
		GetCharacterMovement()->MaxWalkSpeed = RunningMoveSpeed;
	}

	if (PlayerMoveState == MoveState::Stealth) {
		GetCharacterMovement()->MaxWalkSpeed = StealthMoveSpeed;
	}
}

void APlayerCharacter::InputAttack()
{
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
	{
		PlayAnimMontage(AttackMontage);
	}
}

void APlayerCharacter::OnSectionJumpReady(USectionControlNotify* SectionControl)
{
	bEnableControlNotify = true;
	SectionNotify = SectionControl;
}

void APlayerCharacter::OnSectionJumpEnd(USectionControlNotify* SectionControl)
{
	SectionNotify = nullptr;
	bEnableControlNotify = false;
}
