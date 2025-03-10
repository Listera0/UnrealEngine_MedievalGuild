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
	//PrimaryActorTick.TickInterval = 0.5f;

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
	InitPlayerData();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lineTraceCheckTag(FName("Interactable"));

	if (bIsInteract) {
		// 화면에 대상 이름 표시
		ScreenUI->SetVisibility(ESlateVisibility::Visible);
		ScreenUI->SetInteractText(true, "Open");
	}
	else {
		ScreenUI->SetVisibility(ESlateVisibility::Hidden);
	}
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

		if (InteractAction)
			input->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputInteractAction);
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

	if (TradeViewport) {
		TradeUI = CreateWidget<UTrade>(this, TradeViewport);
		TradeUI->AddToViewport();
		TradeUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ScreenViewport) {
		ScreenUI = CreateWidget<UScreenUI>(this, ScreenViewport);
		ScreenUI->AddToViewport();
		ScreenUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::InitPlayerData()
{
	PlayerData = GetPlayerState<APlayerData>();
	PlayerData->PlayerInventoryUI = InventoryUI;
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
	if (InventoryUI->GetVisibility() == ESlateVisibility::Hidden) {
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
				
		int32 screenX; int32 screenY;
		GetViewportSize(screenX, screenY);

		bShowMouseCursor = true;
		SetMouseLocation(screenX * 0.5f, screenY * 0.5f);
	}
	else if (InventoryUI->GetVisibility() == ESlateVisibility::Visible) {
		bShowMouseCursor = false;
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::InputInteractAction(const FInputActionValue& Value)
{
	if (bIsInteract) {
		if (hitResult.GetActor()->ActorHasTag(FName("Coin"))) {
			InventoryUI->Widget_Inventory->MakeItemToSlot(1, 1, 1);
		}
	}
}

FHitResult APlayerCharacterController::lineTraceCheckTag(FName tag)
{
	bIsInteract = false;

	FVector start = GetCharacter()->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
	FRotator cameraRotation = GetControlRotation();
	FVector end = start + cameraRotation.Vector() * 150.0f;

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility);

	//FColor LineColor = bHit ? FColor::Red : FColor::Green;
	//DrawDebugLine(GetWorld(), start, end, LineColor, false, 2.0f, 0, 2.0f);

	if (bHit && hitResult.GetActor()->ActorHasTag(tag)) {
		bIsInteract = true;
		return hitResult;
	}
		
	return FHitResult();
}
