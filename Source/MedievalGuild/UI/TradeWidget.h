// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "../UI/Container_Base.h"

#include "TradeWidget.generated.h"


UCLASS()
class MEDIEVALGUILD_API UTradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass,
						TSubclassOf<UUserWidget> gearWidget);

	void ShowContainer();
	void ShowTotalPrice();
	bool CanMoveItem(EContainerCategory from);
	void SelectBuyItem(FInventoryData* item);
	void ButtonSetting(FColor color);

	UFUNCTION()
	void BindSellBuyButton();

public:
	class APlayerCharacterController* PlayerController;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> GearWidget;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* TradeSlot;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;
	UPROPERTY(meta = (BindWidget))
	UButton* SellBuyButton;

	UContainer_Base* Widget_Trade;

	bool bIsBuy;
	bool bIsSell;
	bool bIsEnoughCurrency;
	int TotalPrice;
	FColor NormalColor = FColor(0.5f, 0.5f, 0.5f, 1.0f);
	FColor FailColor = FColor(0.5f, 0.2f, 0.2f, 1.0f);
	FColor SuccessColor = FColor(0.2f, 0.25f, 0.2f, 1.0f);
};
