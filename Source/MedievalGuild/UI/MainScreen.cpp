// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreen.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/WidgetAnimation.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/TranslateManager.h"
#include "../Character/PlayerCharacter.h"

void UMainScreen::InitMainScreenSetting()
{
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	TArray<AActor*> getActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ACameraActor::StaticClass(), "BackgroundShow", getActors);
	for (AActor* actor : getActors) { CameraActors.Add(Cast<ACameraActor>(actor)); }
	
	PlayerController->SetViewTargetWithBlend(CameraActors[BackGroundIndex], 0.0f);
	BackGroundIndex = 0; SwitchBackGroundMaxTime = 5.0f;
	SetVisibility(ESlateVisibility::Visible);

	StartGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickStartGame);
	NewGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickNewGame);
	Option->OnClicked.AddDynamic(this, &UMainScreen::OnClickOptionMenu);
	ExitGame->OnClicked.AddDynamic(this, &UMainScreen::OnClickExitGame);
}

void UMainScreen::ShowBackgroundScreen(float deltaTime)
{
	SwitchBackGroundTimer += deltaTime;
	if (SwitchBackGroundTimer <= SwitchBackGroundMaxTime) return;
	SwitchBackGroundTimer = 0.0f;

	PlayerController->ScreenEffectUI->StartFadeInAnimation();
	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
		PlayerController->ScreenEffectUI->StartFadeOutAnimation();
		BackGroundIndex = (BackGroundIndex + 1) % CameraActors.Num();
		PlayerController->SetViewTargetWithBlend(CameraActors[BackGroundIndex], 0.0f);
	}, PlayerController->ScreenEffectUI->FadeInAnim->GetEndTime() + 0.1f, false);
}


void UMainScreen::OnClickStartGame()
{
	PlayerController->SetViewTargetWithBlend(PlayerController->GetCharacter(), 0.0f);
	SetVisibility(ESlateVisibility::Collapsed);
	FInputModeGameOnly InputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputMode);
	PlayerController->PlayerData->LoadGame(0);
}

void UMainScreen::OnClickNewGame()
{
	PlayerController->SetViewTargetWithBlend(PlayerController->GetCharacter(), 0.0f);
	SetVisibility(ESlateVisibility::Collapsed);
	FInputModeGameOnly InputMode;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputMode);
	PlayerController->PlayerData->SaveGame();
}

void UMainScreen::OnClickOptionMenu()
{
	if (PlayerController->OptionPanelUI->GetVisibility() == ESlateVisibility::Hidden) { PlayerController->OptionPanelUI->SetVisibility(ESlateVisibility::Visible); }
	else { PlayerController->OptionPanelUI->SetVisibility(ESlateVisibility::Hidden); }
}

void UMainScreen::OnClickExitGame()
{
	Cast<AGameManager>(GetWorld()->GetAuthGameMode())->GameEndSequence();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
