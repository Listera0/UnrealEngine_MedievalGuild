// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "../Item/ItemData.h"
#include "../Quest/Quest_Base.h"
#include "Components/VerticalBox.h"
#include "QuestPlayerPanel.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestPlayerPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class APlayerCharacterController* PlayerController = nullptr;

	void QuestPlayerPanelInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass);
	void ShowQuestList();
	FLinearColor GetQuestSlotColor(EQuestStatus status);

	UPROPERTY()
	TSubclassOf<UUserWidget> QuestSlotClass;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestSlot = nullptr;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* QuestSlotGrid = nullptr;

	TArray<UQuest_Base*> PlayerQuestList;

	FLinearColor BasicColor;
	FLinearColor SuccessColor;
	FLinearColor NotEnoughColor;
};
