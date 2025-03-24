// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI_Base.h"
#include "../Item/ItemDataManager.h"


void UItemUI_Base::SetItemImage(UItemData* item, FVector2D partIndex)
{
	FSlateBrush brush;

	FVector2D origin = FVector2D(1 / (float)(item->width) * partIndex.X, 1 / (float)(item->height) * partIndex.Y);
	FVector2D part = FVector2D(1 / (float)(item->width) * (partIndex.X + 1.0f), 1 / (float)(item->height) * (partIndex.Y + 1.0f));

	brush.SetResourceObject(UItemDataManager::GetInstance()->Get2DSpriteForItem(item));
	brush.SetUVRegion(FBox2D(origin, part));
	brush.TintColor = FLinearColor(1, 1, 1, 1);
	brush.DrawAs = ESlateBrushDrawType::Image;
	brush.Tiling = ESlateBrushTileType::NoTile;

	ItemImage->SetBrush(brush);
	ItemImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UItemUI_Base::SetItemCountText()
{
	UItemUI_Base* lastItemUI = GetCountItem();
	if (lastItemUI->ItemData->ItemData->bStackable) lastItemUI->ItemCountText->SetText(FText::AsNumber(ItemData->ItemCount));
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
	if (GetOwnerItem()->BindItems.Num() != 0) {
		return GetOwnerItem()->BindItems.Last();
	}

	return this;
}
