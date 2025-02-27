// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Character/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (localPlayer) {
		UEnhancedInputLocalPlayerSubsystem* inputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (inputSystem && InputMappingContext) {
			inputSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	InitViewport();
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(InputComponent);

	if (input) {
		if (MoveCamera)
			input->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerCharacterController::InputCameraMove);

		if (MoveAction)
			input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::InputMove);

		if (RunAction) {
			input->BindAction(RunAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputPressRunKey);
			input->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerCharacterController::InputRealeaseRunKey);
		}

		if(StealthAction)
			input->BindAction(StealthAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputStealthToggle);

		if (AttackAction)
			input->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputAttackAction);

		if(InventoryToggle)
			input->BindAction(InventoryToggle, ETriggerEvent::Started, this, &APlayerCharacterController::InputInventoryToggle);
	}
}

void APlayerCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
}

void APlayerCharacterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void APlayerCharacterController::InitViewport()
{
	if (InventoryViewport) {
		InventoryUI = CreateWidget<UPlayerInventory>(this, InventoryViewport);
		InventoryUI->AddToViewport();
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::InputMove(const FInputActionValue& Value)
{
	if (PlayerCharacter) {
		FVector2D inputValue = Value.Get<FVector2D>();

		if(inputValue.Size() > 1.0f)
			inputValue.Normalize();

		FRotator spinRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

		//PlayerCharacter->InputMove(UKismetMathLibrary::GetForwardVector(spinRotator), inputValue.X);
		//PlayerCharacter->InputMove(UKismetMathLibrary::GetRightVector(spinRotator), inputValue.Y);

		FVector Direction = FVector(inputValue.X, inputValue.Y, 0.0f);
		Direction = spinRotator.RotateVector(Direction);
		PlayerCharacter->InputMove(Direction, inputValue.Size());
	}
}

void APlayerCharacterController::InputCameraMove(const FInputActionValue& Value)
{
	FVector2D inputValue = Value.Get<FVector2D>() * CameraSensitive;

	AddYawInput(inputValue.X);
	AddPitchInput(inputValue.Y);
}

void APlayerCharacterController::InputPressRunKey(const FInputActionValue& Value)
{
	PlayerCharacter->InputRunning(true);
}

void APlayerCharacterController::InputRealeaseRunKey(const FInputActionValue& Value)
{
	PlayerCharacter->InputRunning(false);
}

void APlayerCharacterController::InputStealthToggle(const FInputActionValue& Value)
{
	PlayerCharacter->InputStealthToggle();
}

void APlayerCharacterController::InputAttackAction(const FInputActionValue& Value)
{
	PlayerCharacter->InputAttack();
}

void APlayerCharacterController::InputInventoryToggle(const FInputActionValue& Value)
{
	if (InventoryUI->GetVisibility() == ESlateVisibility::Hidden)
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
	else if (InventoryUI->GetVisibility() == ESlateVisibility::Visible)
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
}
