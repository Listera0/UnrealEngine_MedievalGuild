// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/TranslateManager.h"
#include "../Character/PlayerCharacter.h"

void UMainScreen::InitMainScreenSetting()
{
	if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	TArray<AActor*> getActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ACameraActor::StaticClass(), "BackgroundShow", getActors);
	for (AActor* actor : getActors) { CameraActors.Add(Cast<ACameraActor>(actor)); }
	
	PlayerController->SetViewTargetWithBlend(CameraActors[BackGroundIndex], 0.0f);
	BackGroundIndex = 0; SwitchBackGroundMaxTime = 5.0f;
	MainButtonSetting();
	SetVisibility(ESlateVisibility::Visible);

	FInputModeGameAndUI InputMode;
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(InputMode);

	StartGame->OnClicked.Clear();
	StartGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickStartGame);
	NewGame->OnClicked.Clear();
	NewGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickNewGame);
	Option->OnClicked.Clear();
	Option->OnClicked.AddDynamic(this, &UMainScreen::OnClickOptionMenu);
	ExitGame->OnClicked.Clear();
	ExitGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickExitGame);
}

void UMainScreen::MainButtonSetting()
{
	if (UGameplayStatics::DoesSaveGameExist("PlayerSaveData", 0)) {
		StartGame->SetIsEnabled(true);
	}
	else {
		StartGame->SetIsEnabled(false);
	}
}

void UMainScreen::ShowBackgroundScreen(float deltaTime)
{
	SwitchBackGroundTimer += deltaTime;
	if (SwitchBackGroundTimer <= SwitchBackGroundMaxTime) return;
	SwitchBackGroundTimer = 0.0f;

	PlayerController->ScreenEffectUI->StartFadeInAnimation();
	GetWorld()->GetTimerManager().SetTimer(BackTimer, [this]() {
		PlayerController->ScreenEffectUI->StartFadeOutAnimation();
		BackGroundIndex = (BackGroundIndex + 1) % CameraActors.Num();
		PlayerController->SetViewTargetWithBlend(CameraActors[BackGroundIndex], 0.0f);
	}, PlayerController->ScreenEffectUI->FadeInAnim->GetEndTime() + 0.1f, false);
}

void UMainScreen::OnClickStartGame()
{
	GetWorld()->GetTimerManager().ClearTimer(BackTimer);
	SetVisibility(ESlateVisibility::Collapsed);
	FInputModeGameOnly InputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputMode);
	PlayerController->PlayerData->LoadGame(0);
	PlayerController->InventoryUI->Widget_StageMap->MoveToArea("Hideout");
	PlayerController->SetViewTargetWithBlend(PlayerController->GetCharacter(), 0.0f);
}

void UMainScreen::OnClickNewGame()
{
	GetWorld()->GetTimerManager().ClearTimer(BackTimer);
	SetVisibility(ESlateVisibility::Collapsed);
	FInputModeGameOnly InputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputMode);
	PlayerController->InventoryUI->Widget_StageMap->MoveToArea("Tutorial");
	PlayerController->SetViewTargetWithBlend(PlayerController->GetCharacter(), 0.0f);
}

void UMainScreen::OnClickOptionMenu()
{
	if (PlayerController->OptionPanelUI->GetVisibility() == ESlateVisibility::Hidden) { PlayerController->OptionPanelUI->SetVisibility(ESlateVisibility::Visible); }
	else { PlayerController->OptionPanelUI->SetVisibility(ESlateVisibility::Hidden); }
}

void UMainScreen::OnClickExitGame()
{
	//Cast<AGameManager>(GetWorld()->GetAuthGameMode())->GameEndSequence();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
