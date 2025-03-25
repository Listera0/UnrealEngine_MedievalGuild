// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Character/PlayerCharacter.h"
#include "../Item/Test/Test_Item.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameUserSettings.h"


APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickInterval = 0.5f;

}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	InitSceenResolution();
	InitMoveInput();
	InitViewport();
	InitPlayerData();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lineTraceCheckTag(FName("Interactable"));
	CheckScreenUI();
	CheckInteractDistance();
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

void APlayerCharacterController::InitSceenResolution()
{
	FVector2D UserScreenResolution = FVector2D(1920, 1080);
	FIntPoint UserScreenResolutionPoint = FIntPoint(UserScreenResolution.X, UserScreenResolution.Y);

	FSlateApplication::Get().GetActiveTopLevelWindow()->SetSizingRule(ESizingRule::FixedSize);
	FSlateApplication::Get().GetActiveTopLevelWindow()->SetCachedSize(UserScreenResolution);

	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->SetScreenResolution(UserScreenResolutionPoint);
	UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	UserSettings->ApplySettings(false);
}

void APlayerCharacterController::InitMoveInput()
{
	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (localPlayer) {
		UEnhancedInputLocalPlayerSubsystem* inputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (inputSystem && InputMappingContext) {
			inputSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerCharacterController::InitViewport()
{
	int ViewportWidth; int ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);
	ViewPortSize = FVector2D(ViewportWidth, ViewportHeight);

	if (ScreenViewport) {
		ScreenUI = CreateWidget<UScreenUI>(this, ScreenViewport);
		ScreenUI->AddToViewport();
		ScreenUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if (InventoryViewport) {
		InventoryUI = CreateWidget<UPlayerInventory>(this, InventoryViewport);
		InventoryUI->AddToViewport();
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ItemInteractPanel) {
		ItemInteractUI = CreateWidget<UItemInteractPanel>(this, ItemInteractPanel);
		ItemInteractUI->AddToViewport();
		ItemInteractUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ItemInfoViewport) {
		ItemInfoUI = CreateWidget<UItemInfoPanel>(this, ItemInfoViewport);
		ItemInfoUI->AddToViewport();
		ItemInfoUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::InitPlayerData()
{
	PlayerData = GetPlayerState<APlayerData>();
	PlayerData->PlayerInventoryUI = InventoryUI;
	PlayerData->PlayerEquipment.Init(nullptr, 5);
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
	if (!bIsUIOpened) {
		FVector2D inputValue = Value.Get<FVector2D>() * CameraSensitive;

		AddYawInput(inputValue.X);
		AddPitchInput(inputValue.Y);
	}
}

void APlayerCharacterController::InputPressRunKey(const FInputActionValue& Value)
{
	PlayerCharacter->InputRunning(true);
	bIsShiftPressed = true;
}

void APlayerCharacterController::InputRealeaseRunKey(const FInputActionValue& Value)
{
	PlayerCharacter->InputRunning(false);
	bIsShiftPressed = false;
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
		InventoryUI->PanelVisibleSetting(0);
		OpenUISetting();
		InventoryUI->Widget_Inventory->ShowContainer(PlayerData->PlayerInventory);
		InventoryUI->Widget_Equipment->ShowContainer();
	}
	else if (InventoryUI->GetVisibility() == ESlateVisibility::Visible) {
		AllUIHidden();
	}
}

void APlayerCharacterController::InputInteractAction(const FInputActionValue& Value)
{
	// UI가 열려있을 때
	if (bIsInteractAction) {
		AllUIHidden();
	}
	else {
		if (bIsInteract) {
			if (hitResult.GetActor()->ActorHasTag(FName("Item"))) {
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				FInventoryData* targetItem = InteractObj->ContainerInventory[0];
				targetItem->SlotIndex = FVector2D(-1.0f);
				PlayerData->AddItemToAllWork(PlayerData->PlayerInventory, targetItem, InventoryUI->Widget_Inventory);
				hitResult.GetActor()->Destroy();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Container"))) {
				InventoryUI->PanelVisibleSetting(1);
				OpenUISetting();

				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->SetContainerUI();
				InventoryUI->Widget_Inventory->ShowContainer(PlayerData->PlayerInventory);
				InventoryUI->Widget_Equipment->ShowContainer();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Storage"))) {
				InventoryUI->PanelVisibleSetting(2);
				OpenUISetting();

				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InventoryUI->Widget_Equipment->ShowContainer();
				InventoryUI->Widget_Inventory->ShowContainer(PlayerData->PlayerInventory);
				InventoryUI->Widget_Storage->ShowContainer(PlayerData->PlayerStorage);
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Merchant"))) {
				InventoryUI->PanelVisibleSetting(3);
				OpenUISetting();

				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());

				InteractObj->SetContainerUI();
				InventoryUI->Widget_Trade->ShowContainer();
				InventoryUI->Widget_Storage->ShowContainer(PlayerData->PlayerStorage);

			}
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

void APlayerCharacterController::CheckScreenUI()
{
	if (bIsInteract) {
		// 화면에 대상 이름 표시
		ScreenUI->SetVisibility(ESlateVisibility::Visible);
		ScreenUI->SetInteractText(true, "Open");
	}
	else {
		ScreenUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::CheckInteractDistance()
{
	if (bIsInteractAction && InteractObj) {
		if (FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation()) > 40000.0f) {
			AllUIHidden();
		}
	}
}

void APlayerCharacterController::OpenUISetting()
{
	bIsUIOpened = true;
	InventoryUI->SetVisibility(ESlateVisibility::Visible);

	// Mouse mode 설정 - 마우스 표시 및 중앙으로 이동
	bShowMouseCursor = true;
	int32 screenX; int32 screenY;
	GetViewportSize(screenX, screenY);
	SetMouseLocation(screenX * 0.5f, screenY * 0.5f);

	// Mouse mode 설정 - 마우스로 UI클릭 가능하게 설정
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(InventoryUI->TakeWidget());
	SetInputMode(InputMode);
}

void APlayerCharacterController::AllUIHidden()
{
	if (InteractObj && InteractObj->ActorHasTag("Merchant")) { InventoryUI->Widget_Trade->ResetContainer(); }

	bIsUIOpened = false;
	bIsInteractAction = false;
	bShowMouseCursor = false;
	InteractObj = nullptr;
	InventoryUI->SetVisibility(ESlateVisibility::Hidden);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

UContainer_Base* APlayerCharacterController::GetTargetContainer(EContainerCategory category)
{
	switch (category) {
		case EContainerCategory::Inventory: return InventoryUI->Widget_Inventory; break;
		case EContainerCategory::Storage: return InventoryUI->Widget_Storage; break;
		case EContainerCategory::Trade: return InventoryUI->Widget_Trade->Widget_Trade; break;
		case EContainerCategory::Container: return InventoryUI->Widget_Container; break;
		case EContainerCategory::Merchant: return  InventoryUI->Widget_Merchant; break;
		case EContainerCategory::Helmet: return InventoryUI->Widget_Equipment->Widget_Helmet; break;
		case EContainerCategory::Cloth: return InventoryUI->Widget_Equipment->Widget_Cloth; break;
		case EContainerCategory::Shoes: return InventoryUI->Widget_Equipment->Widget_Shoes; break;
		case EContainerCategory::Bag: return InventoryUI->Widget_Equipment->Widget_Bag; break;
		case EContainerCategory::Weapon: return InventoryUI->Widget_Equipment->Widget_Weapon; break;
	}

	return nullptr;
}

void APlayerCharacterController::RecordMousePosition(FVector2D position)
{
	bIsInteractItem = true;

}
