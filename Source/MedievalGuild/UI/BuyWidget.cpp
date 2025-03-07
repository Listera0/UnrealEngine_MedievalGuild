// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyWidget.h"

void UBuyWidget::InitSetting()
{

}

void UBuyWidget::SetNewItem()
{
	// own currency
	// price

	// own currency > 0
	OwnText->SetColorAndOpacity(FSlateColor(FColor(1.0f, 0.2f, 0.2f, 1.0f)));

	OwnText->SetColorAndOpacity(FSlateColor(FColor(0.3f, 1.0f, 0.3f, 1.0f)));

	OwnText->SetText(FText::FromString(FString::Printf(TEXT("%d"), 1000)));
	PriceText->SetText(FText::FromString(FString::Printf(TEXT("/ %d"), 1000)));
}
