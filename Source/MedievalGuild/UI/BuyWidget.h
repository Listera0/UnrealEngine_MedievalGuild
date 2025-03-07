// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

#include "BuyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UBuyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSetting();
	void SetNewItem();

public:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ItemSlot;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnText;

	UPROPERTY(meta = (BindWidget))
	UButton* BuyButon;
};
