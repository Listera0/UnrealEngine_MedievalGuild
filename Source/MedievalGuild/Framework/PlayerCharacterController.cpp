// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "../Character/PlayerCharacter.h"
#include "../Item/Test/Test_Item.h"
#include "../Object/IInteractInterface.h"
#include "../Dialogue/DialogueComponent.h"


APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickInterval = 0.5f;

}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	InitPlayerCameraLock();
	InitSceenResolution();
	InitMoveInput();
	InitViewport();
	InitPlayerData();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MainMenuUI->GetVisibility() == ESlateVisibility::Visible) { MainMenuUI->ShowBackgroundScreen(DeltaTime); }
	InitViewportScale();
	lineTraceCheckTag(FName("Interactable"));
	CheckScreenUI();
	CheckInteractDistance();
	CheckInteractUIDistance();
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(InputComponent);

	if (input) {
		if (MoveCamera) input->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerCharacterController::InputCameraMove);
		if (MoveAction) input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::InputMove);
		if (RunAction) input->BindAction(RunAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputPressRunKey);
		if (RunAction) input->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerCharacterController::InputRealeaseRunKey);
		if (StealthAction) input->BindAction(StealthAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputStealthToggle);
		if (AttackAction) input->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputAttackAction);
		if (AttackAction2) input->BindAction(AttackAction2, ETriggerEvent::Started, this, &APlayerCharacterController::InputAttack2Action);
		if (InventoryToggle) input->BindAction(InventoryToggle, ETriggerEvent::Started, this, &APlayerCharacterController::InputInventoryToggle);
		if (InteractAction) input->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::InputInteractAction);
	}
}

void APlayerCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	TSManager = Cast<ATranslateManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATranslateManager::StaticClass()));
}

void APlayerCharacterController::OnUnPossess()
{
	Super::OnUnPossess();
}

void APlayerCharacterController::InitPlayerCameraLock()
{
	PlayerCameraManager->ViewPitchMin = -40.0f;
	PlayerCameraManager->ViewPitchMax = 40.0f;
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

	if (ScreenEffectWidget) {
		ScreenEffectUI = CreateWidget<UScreenEffectWidget>(this, ScreenEffectWidget);
		ScreenEffectUI->AddToViewport();
		ScreenEffectUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if (MainMenuPanel) {
		MainMenuUI = CreateWidget<UMainScreen>(this, MainMenuPanel);
		MainMenuUI->AddToViewport();
		MainMenuUI->InitMainScreenSetting();

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

	if (OptionPanelWidget) {
		OptionPanelUI = CreateWidget<UOptionPanel>(this, OptionPanelWidget);
		OptionPanelUI->AddToViewport();
		OptionPanelUI->InitMainScreenSetting();
		OptionPanelUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacterController::InitPlayerData()
{
	PlayerData = GetPlayerState<APlayerData>();
	PlayerData->PlayerInventoryUI = InventoryUI;
	PlayerData->PlayerEquipment.Init(nullptr, 5);
	CurrentPlayerLocation = "Hideout";
}

void APlayerCharacterController::InputMove(const FInputActionValue& Value)
{
	if (MainMenuUI->GetVisibility() == ESlateVisibility::Visible) return;
	if (ScreenEffectUI->CheckPlayingAnimation()) return;

	if (PlayerCharacter && !PlayerCharacter->CheckAttackAnim() && !PlayerCharacter->CheckDeathAnim() ) {
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
	if (MainMenuUI->GetVisibility() == ESlateVisibility::Visible) return;

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
	if (!bIsUIOpened) PlayerCharacter->InputAttack(0);
}

void APlayerCharacterController::InputAttack2Action(const FInputActionValue& Value)
{
	if (!bIsUIOpened) PlayerCharacter->InputAttack(1);
}

void APlayerCharacterController::InputInventoryToggle(const FInputActionValue& Value)
{
	if (MainMenuUI->GetVisibility() == ESlateVisibility::Visible) return;

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
	if (bIsInteractAction && !bIsTalking) {
		AllUIHidden();
	}
	else {
		if (bIsInteract) {
			if (hitResult.GetActor()->ActorHasTag(FName("Dead"))) {
				bIsInteractAction = true;
				InteractCharacter = Cast<AEnemy_1>(hitResult.GetActor());
				Cast<IInteractInterface>(InteractCharacter)->SetInteractDistance(FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractCharacter->GetActorLocation()));
				InventoryUI->PanelVisibleSetting(7);
				OpenUISetting();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Item"))) {
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				FInventoryData* targetItem = InteractObj->ContainerInventory[0];
				targetItem->SlotIndex = FVector2D(-1.0f);
				PlayerData->AddItemToAllWork(PlayerData->PlayerInventory, targetItem, InventoryUI->Widget_Inventory);
				OnGetItem.Broadcast(targetItem->ItemData->index);
				hitResult.GetActor()->Destroy();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Container"))) {
				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				InventoryUI->PanelVisibleSetting(1);
				OpenUISetting();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Storage"))) {
				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				InventoryUI->PanelVisibleSetting(2);
				OpenUISetting();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Merchant"))) {
				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				InventoryUI->PanelVisibleSetting(3);
				OpenUISetting();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("NPC"))) {
				bIsInteractAction = true;
				bIsTalking = true;

				if (!bNotFirstTalking) {
					InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
					InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				}

				DialogueProgress();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Door"))) {
				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				InventoryUI->PanelVisibleSetting(11);
				OpenUISetting();
			}
			else if (hitResult.GetActor()->ActorHasTag(FName("Anvil"))) {
				bIsInteractAction = true;
				InteractObj = Cast<AInteractObject_Base>(hitResult.GetActor());
				InteractObj->InteractDistance = FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation());
				InventoryUI->PanelVisibleSetting(6);
				OpenUISetting();
			}
		}
	}	
}

FHitResult APlayerCharacterController::lineTraceCheckTag(FName tag)
{
	bIsInteract = false;

	FVector start = GetCharacter()->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
	if (PlayerCharacter->PlayerMoveState == MoveState::Stealth) { start -= FVector(0.0f, 0.0f, 50.0f); }
	FVector boxSize = FVector(5.0f, 5.0f, 5.0f);
	FRotator cameraRotation = GetControlRotation();
	FVector end = start + cameraRotation.Vector() * 150.0f;

	bool bHit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeBox(boxSize));
	//bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility);

	//FColor LineColor = bHit ? FColor::Red : FColor::Green;
	//DrawDebugBox(GetWorld(), hitResult.Location, boxSize, FQuat::Identity, LineColor, false, 2.0f, 0, 2.0f);
	//DrawDebugLine(GetWorld(), start, end, LineColor, false, 2.0f, 0, 2.0f);

	if (bHit && hitResult.GetActor()->ActorHasTag(tag)) {
		bIsInteract = true;
		return hitResult;
	}
		
	return FHitResult();
}

void APlayerCharacterController::InitViewportScale()
{
	if (!bIsViewScaleInit && UWidgetLayoutLibrary::GetViewportSize(this).X != 0.0f) {
		FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
		//FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		FVector2D ScreenResolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
		FVector2D Scale = ViewportSize / ScreenResolution;
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::Printf(TEXT("ViewPortScale : (%f, %f)"), Scale.X, Scale.Y));
		bIsViewScaleInit = true;
	}
}

void APlayerCharacterController::CheckScreenUI()
{
	if (bIsInteract) {
		if (hitResult.GetActor()->ActorHasTag(FName("Item"))) { 
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString(Cast<AInteractObject_Base>(hitResult.GetActor())->ContainerInventory[0]->ItemData->name)).ToString());
		}
		else if(hitResult.GetActor()->ActorHasTag(FName("Container"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Search")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("Storage"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Storage")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("Door"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Leave")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("Merchant"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Trade")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("NPC"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Talk")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("Anvil"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Work")).ToString());
		}
		else if (hitResult.GetActor()->ActorHasTag(FName("Enemy"))) {
			ScreenUI->SetInteractText(true, TSManager->TranslateTexts(FText::FromString("Search")).ToString());
		}
	}
	else {
		ScreenUI->SetInteractText(false, "");
	}
}

void APlayerCharacterController::CheckInteractDistance()
{
	if (bIsInteractAction) {
		if (InteractObj) {
			if (FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractObj->GetActorLocation()) > 
					Cast<IInteractInterface>(InteractObj)->GetInteractDistance() + 15000.0f) {
				AllUIHidden();
			}
		}
		else if (InteractCharacter) {
			if (FVector::DistSquared(PlayerCharacter->GetActorLocation(), InteractCharacter->GetActorLocation()) > 
					Cast<IInteractInterface>(InteractCharacter)->GetInteractDistance() + 15000.0f) {
				AllUIHidden();
			}
		}
	}
}

void APlayerCharacterController::CheckInteractUIDistance()
{
	if (bIsInteractItem) {
		float MouseX; float MouseY; float SlotSize = 100.0f; float PanelOffSet = 100.0f;
		if (GetMousePosition(MouseX, MouseY)) {
			FVector2D CurrentMousePosition(MouseX, MouseY);
			FVector2D DistancePosition = LastMousePosition - CurrentMousePosition;
			FVector2D UISize = FVector2D((float)(ItemInteractUI->InteractItem->ItemData->width), (float)(ItemInteractUI->InteractItem->ItemData->height));
			
			if (CurrentMousePosition.X < LastMousePosition.X - SlotSize * UISize.X ||
				CurrentMousePosition.X > LastMousePosition.X + SlotSize * UISize.X + PanelOffSet ||
				CurrentMousePosition.Y < LastMousePosition.Y - SlotSize * UISize.Y ||
				CurrentMousePosition.Y > LastMousePosition.Y + SlotSize * UISize.Y)
			{
				bIsInteractItem = false;
				ItemInteractUI->SetVisibility(ESlateVisibility::Hidden);
			}
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
	if (InteractObj) {
		if (InteractObj->ActorHasTag("Merchant")) {
			InventoryUI->Widget_Trade->ResetContainer();
			if (InventoryUI->Widget_Merchant->bIsSwitched) {
				InventoryUI->Widget_Merchant->SwitchPanelScreen();
			}
		}
		else if (InteractObj->ActorHasTag("Anvil")) {
			InventoryUI->Widget_CraftRequire->ResetRequireList();
		}
		else if (InteractObj->ActorHasTag("NPC")) {
			ScreenUI->SetDialogueText(false, "");
		}
	}

	bIsUIOpened = false;
	bIsInteractAction = false;
	bIsTalking = false;
	bNotFirstTalking = false;
	bShowMouseCursor = false;
	InteractObj = nullptr;
	InteractCharacter = nullptr;
	InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	OptionPanelUI->SetVisibility(ESlateVisibility::Hidden);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void APlayerCharacterController::StaticUITranslate()
{
	InventoryUI->Widget_CraftRequire->RequireText->SetText(TSManager->TranslateTexts(FText::FromString("Require Item List")));
	InventoryUI->Widget_CraftRequire->CraftText->SetText(TSManager->TranslateTexts(FText::FromString("Craft")));

	InventoryUI->Widget_QuestPlayerPanel->QuestText->SetText(TSManager->TranslateTexts(FText::FromString("Quest List")));

	InventoryUI->Widget_OptionMenu->InvText->SetText(TSManager->TranslateTexts(FText::FromString("Inventory")));
	InventoryUI->Widget_OptionMenu->QuestText->SetText(TSManager->TranslateTexts(FText::FromString("Quest")));
	InventoryUI->Widget_OptionMenu->OptionText->SetText(TSManager->TranslateTexts(FText::FromString("Option")));
	InventoryUI->Widget_OptionMenu->ExitText->SetText(TSManager->TranslateTexts(FText::FromString("Exit")));

	InventoryUI->Widget_StageMap->LibraryText->SetText(TSManager->TranslateTexts(FText::FromString("Library")));
	InventoryUI->Widget_StageMap->LockText1->SetText(TSManager->TranslateTexts(FText::FromString("Lock")));
	InventoryUI->Widget_StageMap->LockText2->SetText(TSManager->TranslateTexts(FText::FromString("Lock")));

	MainMenuUI->StartGameText->SetText(TSManager->TranslateTexts(FText::FromString("Load")));
	MainMenuUI->NewGameText->SetText(TSManager->TranslateTexts(FText::FromString("New")));
	MainMenuUI->OptionText->SetText(TSManager->TranslateTexts(FText::FromString("Option")));
	MainMenuUI->ExitGameText->SetText(TSManager->TranslateTexts(FText::FromString("Exit")));
}

void APlayerCharacterController::DialogueProgress()
{
	UDialogueComponent* dialogueComponent = Cast<UDialogueComponent>(hitResult.GetActor()->FindComponentByClass(UDialogueComponent::StaticClass()));
	UDialogue* currentDia = dialogueComponent->GetCurrentDialogue();

	if (!currentDia) return;

	if (!bNotFirstTalking) {
		dialogueIndex = -1; totalIndex = currentDia->Responses.Num();
		bNotFirstTalking = true;
	}

	dialogueIndex++;
	int dialogueOptionValue = -1;

	if (dialogueIndex == totalIndex) {
		if (currentDia->bIsDialogueOption) {
			dialogueOptionValue = 0;
		}

		dialogueComponent->EndDialogue(dialogueOptionValue);
		bNotFirstTalking = false;
		bIsTalking = false;
		ScreenUI->SetDialogueText(false, "");
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, TSManager->TranslateTexts(currentDia->Responses[dialogueIndex]));
	ScreenUI->SetDialogueText(true, TSManager->TranslateTexts(currentDia->Responses[dialogueIndex]));
}

UContainer_Base* APlayerCharacterController::GetTargetContainer(EContainerCategory category)
{
	switch (category) {
		case EContainerCategory::Inventory: return InventoryUI->Widget_Inventory; break;
		case EContainerCategory::Storage: return InventoryUI->Widget_Storage; break;
		case EContainerCategory::Trade: return InventoryUI->Widget_Trade->Widget_Trade; break;
		case EContainerCategory::Container: return InventoryUI->Widget_Container; break;
		case EContainerCategory::Merchant: return  InventoryUI->Widget_Merchant; break;
		case EContainerCategory::CraftInventory: return  InventoryUI->Widget_CraftInventory; break;
		case EContainerCategory::EnemyInventory: return  InventoryUI->Widget_EnemyContainer; break;
		case EContainerCategory::Helmet: return InventoryUI->Widget_Equipment->Widget_Helmet; break;
		case EContainerCategory::Cloth: return InventoryUI->Widget_Equipment->Widget_Cloth; break;
		case EContainerCategory::Shoes: return InventoryUI->Widget_Equipment->Widget_Shoes; break;
		case EContainerCategory::Bag: return InventoryUI->Widget_Equipment->Widget_Bag; break;
		case EContainerCategory::Weapon: return InventoryUI->Widget_Equipment->Widget_Weapon; break;
	}

	return nullptr;
}

void APlayerCharacterController::RecordMousePosition()
{
	bIsInteractItem = true;
	GetMousePosition(LastMousePosition.X, LastMousePosition.Y);
}
