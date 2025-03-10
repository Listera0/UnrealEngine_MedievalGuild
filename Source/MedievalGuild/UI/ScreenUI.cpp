// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUI.h"

void UScreenUI::SetInteractText(bool visible, FString text)
{
	InteractText->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	InteractText->SetText(FText::FromString(text));
}
