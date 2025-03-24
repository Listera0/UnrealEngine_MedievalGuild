// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "../Object/InventoryData.h"

#include "ItemInfoPanel.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemInfoPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SettingItem(FInventoryData* data);

protected:
	FString GetItemType(FInventoryData* data);
	void OpenPanel(FInventoryData* data);
	UFUNCTION() 
	void ClosePanel();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemInfo;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TagValue;
};
