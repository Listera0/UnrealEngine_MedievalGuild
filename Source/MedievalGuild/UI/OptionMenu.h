// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
