// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI_Base.h"

void UItemUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemUI_Base::SetItemCountText()
{
	if (bStackable)
		ItemCountText->SetText(FText::AsNumber(ItemCount));
	else
		ItemCountText->SetText(FText());
}

void UItemUI_Base::SetItemBind(TArray<UItemUI_Base*> items)
{
	BindItems.Empty();
	BindItems.Append(items);
}
