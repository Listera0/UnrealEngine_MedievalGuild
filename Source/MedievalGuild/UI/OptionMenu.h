// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OptionMenu.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UOptionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class APlayerCharacterController* PlayerController = nullptr;

	void OptionMenuInitSetting();

	UPROPERTY(meta = (BindWidget))
	UButton* ShowInventory = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ShowQuest = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ShowOption = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGame = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InvText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OptionText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExitText = nullptr;

protected:
	UFUNCTION()
	void OnClickShowInventory();
	UFUNCTION()
	void OnClickShowQuest();
	UFUNCTION()
	void OnClickShowOption();
	UFUNCTION()
	void OnClickExitGame();
};
