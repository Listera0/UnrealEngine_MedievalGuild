// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Container_Base.h"
#include "Components/VerticalBox.h"
#include "MerchantInventory.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UMerchantInventory : public UContainer_Base
{
	GENERATED_BODY()
	
public:
	class APlayerCharacterController* PlayerController = nullptr;

	virtual void ShowContainer(TArray<FInventoryData*>& data) override;

	void MerchantPanelInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size);
	void MakeQuestListPanel();
	UFUNCTION()
	void SwitchPanelScreen();

	UPROPERTY()
	TSubclassOf<UUserWidget> QuestSlotClass;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* QuestSlot = nullptr;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* QuestSlotGrid = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MerchantName = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* TradeAndQuest = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TradeAndQuestText = nullptr;

	UPROPERTY()
	TArray<UUserWidget*> QuestList;
	bool bIsSwitched;
};
