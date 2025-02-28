// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI_Base.h"

void UItemUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemUI_Base::SetItemCount(int count)
{
	ItemCount = count;
	bStackable = true;
	ItemCountText->SetText(FText::AsNumber(ItemCount));
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

void UItemUI_Base::SetDuplicateInit(UItemUI_Base* target)
{
	target->bStackable = bStackable;
	target->ItemCount = ItemCount;
	target->SetItemBind(BindItems);
	target->SetItemCountText();
	target->SetItemSize(ItemSizeX, ItemSizeY);
	target->SetItemIndex(ItemIndexX, ItemIndexY);
}

void UItemUI_Base::SetItemIndex(int x, int y)
{
	ItemIndexX = x; ItemIndexY = y;
}

void UItemUI_Base::SetItemSize(int x, int y)
{
	ItemSizeX = x; ItemSizeY = y;
}
