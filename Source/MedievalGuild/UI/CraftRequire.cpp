// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftRequire.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "CraftRequireItem.h"

void UCraftRequire::CraftRequireInitSetting(TSubclassOf<UUserWidget> requireItem)
{
	CraftRequireItemClass = requireItem;

	NotEnoughColor = FLinearColor(0.5f, 0.2f, 0.2f, 1.0f);
	EnoughColor = FLinearColor(0.2f, 0.5f, 0.2f, 1.0f);

	CraftButton->OnClicked.AddDynamic(this, &UCraftRequire::CreateItem);
}

void UCraftRequire::ResetRequireList()
{
	ItemList->ClearChildren();
	CraftButtonSetting(FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
}

void UCraftRequire::ShowRequireList(FInventoryData* data)
{
	ItemList->ClearChildren();
	SelectItemData = data;
	int itemLength = 2;

	if (data != nullptr) {
		UCanvasPanelSlot* BoxSlot = Cast<UCanvasPanelSlot>(ItemList->Slot);
		BoxSlot->SetSize(FVector2D(500.0f, (float)(100 * itemLength)));

		for (int i = 0; i < itemLength; i++) {
			UCraftRequireItem* newItem = CreateWidget<UCraftRequireItem>(GetWorld(), CraftRequireItemClass);
			newItem->SetItemInfo();

			UVerticalBoxSlot* newItemSlot = ItemList->AddChildToVerticalBox(newItem);
			newItemSlot->SetPadding(FMargin());
			newItemSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			newItemSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			newItemSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}

		//CheckSatisfiedRequire();
	}
	else {
		ResetRequireList();
	}
}

bool UCraftRequire::CheckSatisfiedRequire()
{
	bool checkResult = true;

	for (UWidget* widget : ItemList->GetAllChildren()) {
		Cast<UCraftRequireItem>(widget)->SetItemInfo();

		if (nullptr) {
			checkResult = false;
			break;
		}
	}

	checkResult ? CraftButtonSetting(EnoughColor) : CraftButtonSetting(NotEnoughColor);

	return checkResult;
}

void UCraftRequire::CraftButtonSetting(FLinearColor color)
{
	FButtonStyle buttonStyle;
	FSlateBrush borderBrush;
	FSlateBrushOutlineSettings outlineBrush;

	outlineBrush.RoundingType = ESlateBrushRoundingType::FixedRadius;
	outlineBrush.Width = 1.0f;
	outlineBrush.CornerRadii = FVector4(4.0f, 4.0f, 4.0f, 4.0f);

	borderBrush.TintColor = FSlateColor(color);
	borderBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	borderBrush.OutlineSettings = outlineBrush;

	buttonStyle.SetNormal(borderBrush);
	buttonStyle.SetHovered(borderBrush);
	buttonStyle.SetPressed(borderBrush);
	buttonStyle.NormalPadding = 0.0f;
	buttonStyle.PressedPadding = 0.0f;
	CraftButton->SetStyle(buttonStyle);
}

void UCraftRequire::CreateItem()
{
	if (SelectItemData != nullptr && CheckSatisfiedRequire()) {
		// get item
		// remove item
		CheckSatisfiedRequire();
	}
}
