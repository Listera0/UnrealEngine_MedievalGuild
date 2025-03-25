// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoPanel.h"
#include "../Item/ItemDataManager.h"

void UItemInfoPanel::NativeConstruct()
{
	Super::NativeConstruct();

	CancelButton->OnClicked.AddDynamic(this, &UItemInfoPanel::ClosePanel);
}

void UItemInfoPanel::SettingItem(FInventoryData* data)
{
	// 이미지 넣기
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(UItemDataManager::GetInstance()->Get2DSpriteForItem(data->ItemData));
	ItemImage->SetBrush(NewBrush);

	// 슬롯 설정
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
	PanelSlot->SetSize(FVector2D((float)(data->ItemData->width) * 100.0f, (float)(data->ItemData->height) * 100.0f));

	// 정보 설정
	ItemName->SetText(FText::FromString(data->ItemData->name));
	ItemInfo->SetText(FText::FromString(data->ItemData->description + FString::Printf(TEXT("\n(Max %d)"), data->ItemData->maxStack)));
	ItemValue->SetText(FText::FromString(FString::Printf(TEXT("%d G"), (int)(data->ItemData->price))));
	TagValue->SetText(FText::FromString(GetItemType(data)));
}

FString UItemInfoPanel::GetItemType(FInventoryData* data)
{
	FString returnValue = "";

	switch (data->ItemData->eItemType)
	{
	case EItemType::Consumeable:
		returnValue.Append("Consumeable"); break;
	case EItemType::Currency:
		returnValue.Append("Currency"); break;
	case EItemType::Helmet:
		returnValue.Append("Helmet"); break;
	case EItemType::Cloth:
		returnValue.Append("Cloth"); break;
	case EItemType::Shoes:
		returnValue.Append("Shoes"); break;
	case EItemType::Bag:
		returnValue.Append("Bag"); break;
	case EItemType::Weapon:
		returnValue.Append("Weapon"); break;
	default:
		returnValue.Append("None"); break;
	}

	return returnValue;
}

void UItemInfoPanel::OpenPanel(FInventoryData* data)
{
	SetVisibility(ESlateVisibility::Visible);
	SettingItem(data);
}

void UItemInfoPanel::ClosePanel()
{
	SetVisibility(ESlateVisibility::Hidden);
}