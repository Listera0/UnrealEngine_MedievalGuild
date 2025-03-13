// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI_Base.h"

void UItemUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemUI_Base::SetItemCountText()
{
	UItemUI_Base* lastItemUI = GetCountItem();
	if (lastItemUI->ItemData->ItemData->eItemType == EItemType::None) lastItemUI->ItemCountText->SetText(FText::AsNumber(ItemData->ItemCount));
	else lastItemUI->ItemCountText->SetText(FText());
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
