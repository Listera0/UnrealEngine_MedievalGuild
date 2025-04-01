// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "../Quest/Quest_Base.h"
#include "QuestInfoPanel.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestInfoPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class APlayerCharacterController* PlayerController = nullptr;

	void QuestInfoInitSetting();
	void ShowQuestDetail(UQuest_Base* data);
	void CheckQuestProgress();
	bool CheckApplyQuest();
	bool CheckSuccessQuest();
	void SetInteractButtonColor(FLinearColor color);

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestDetailPanel;
	UPROPERTY(meta = (BindWidget))
	UButton* QuestInteractButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestInfo;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TargetValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RewardValue;

	UQuest_Base* SelectQuest;

	FLinearColor BasicColor;
	FLinearColor SuccessColor;
	FLinearColor NotEnoughColor;

protected:
	UFUNCTION()
	void OnClickInteractButton();
};
