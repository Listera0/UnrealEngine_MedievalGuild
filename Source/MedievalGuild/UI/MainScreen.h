// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MainScreen.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UMainScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitMainScreenSetting();
	void ShowBackgroundScreen(float deltaTime);

public:
	UFUNCTION()
	void OnClickStartGame();
	UFUNCTION()
	void OnClickNewGame();
	UFUNCTION()
	void OnClickOptionMenu();
	UFUNCTION()
	void OnClickExitGame();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGame = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* NewGame = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* Option = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGame = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartGameText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NewGameText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExitGameText = nullptr;

public:
	class APlayerCharacterController* PlayerController = nullptr;

	TArray<ACameraActor*> CameraActors;
	int BackGroundIndex;
	float SwitchBackGroundTimer;
	float SwitchBackGroundMaxTime;
};
