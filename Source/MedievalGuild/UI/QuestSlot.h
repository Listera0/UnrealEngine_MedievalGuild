// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "QuestSlot.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* QuestSlot;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestName;

	int QuestIndex;

	void SetQuestInfo(FText name);
	UFUNCTION()
	void ShowQuestDetail();
};
