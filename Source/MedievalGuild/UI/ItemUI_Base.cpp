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
	target->SetItemIndex(ItemIndex);
	target->SetItemSize(ItemSize);
}

UItemUI_Base* UItemUI_Base::GetOwnerItem()
{
	for (int i = 0; i < BindItems.Num(); i++) {
		if ((int)(BindItems[i]->ItemIndex.X) == 0 && (int)(BindItems[i]->ItemIndex.Y) == 0) {
			return BindItems[i];
		}
	}

	return this;
}

UItemUI_Base* UItemUI_Base::GetCountItem()
{
	if (BindItems.Num() > 0) {
		if(BindItems.Last())
			return BindItems.Last();
	}

	return this;
}
