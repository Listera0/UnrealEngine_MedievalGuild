// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftRequire.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "CraftRequireItem.h"
#include "../Framework/PlayerCharacterController.h"

void UCraftRequire::CraftRequireInitSetting(TSubclassOf<UUserWidget> requireItem)
{
	CraftRequireItemClass = requireItem;

	NotEnoughColor = FLinearColor(0.5f, 0.2f, 0.2f, 1.0f);
	EnoughColor = FLinearColor(0.2f, 0.5f, 0.2f, 1.0f);

	CraftButton->OnClicked.AddDynamic(this, &UCraftRequire::CreateItem);

	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}

void UCraftRequire::ResetRequireList()
{
	ItemListWidget->ClearChildren();
	CraftButtonSetting(FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
}

void UCraftRequire::ShowRequireList(FInventoryData* data)
{
	ItemListWidget->ClearChildren();
	SelectItemData = data;
	selectRecipe = UItemDataManager::GetInstance()->FindItemRecipe(data->ItemData->index)[0];

	if (data != nullptr) {
		UCanvasPanelSlot* BoxSlot = Cast<UCanvasPanelSlot>(ItemListWidget->Slot);
		BoxSlot->SetSize(FVector2D(500.0f, (float)(100 * selectRecipe->IngredientsAmount.Num())));

		for (int i = 0; i < selectRecipe->IngredientsAmount.Num(); i++) {
			UCraftRequireItem* newItem = CreateWidget<UCraftRequireItem>(GetWorld(), CraftRequireItemClass);
			UVerticalBoxSlot* newItemSlot = ItemListWidget->AddChildToVerticalBox(newItem);
			newItemSlot->SetPadding(FMargin());
			newItemSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			newItemSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			newItemSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}

		CheckSatisfiedRequire();
	}
	else {
		ResetRequireList();
	}
}

bool UCraftRequire::CheckSatisfiedRequire()
{
	bool checkResult = true;
	TArray<UWidget*> widgets = ItemListWidget->GetAllChildren();

	for (int i = 0; i < selectRecipe->IngredientsIndex.Num(); i++) {
		int itemCount = 0;
		FInventoryData* inventoryItem = PlayerController->PlayerData->HasItem(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Inventory), selectRecipe->IngredientsIndex[i], false);
		if (inventoryItem) itemCount += inventoryItem->ItemCount;
		FInventoryData* storageItem = PlayerController->PlayerData->HasItem(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), selectRecipe->IngredientsIndex[i], false);
		if (storageItem) itemCount += storageItem->ItemCount;
		
		Cast<UCraftRequireItem>(widgets[i])->SetItemInfo(selectRecipe->IngredientsIndex[i], itemCount, selectRecipe->IngredientsAmount[i]);
		if (itemCount < selectRecipe->IngredientsAmount[i]) { checkResult = false; }
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
		FInventoryData* newItem = new FInventoryData(FVector2D(-1.0f), SelectItemData->ItemData, selectRecipe->MakeItemAmount);
		PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), newItem, PlayerController->GetTargetContainer(EContainerCategory::Storage));

		for (int i = 0; i < selectRecipe->IngredientsAmount.Num(); i++) {
			UItemData* itemData = UItemDataManager::GetInstance()->FindItemData(selectRecipe->IngredientsIndex[i]);
			int remainCount = PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Inventory), itemData, selectRecipe->IngredientsAmount[i], true);
			if(remainCount > 0) PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), itemData, remainCount, true);
		}

		PlayerController->InventoryUI->Widget_Storage->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage));
		CheckSatisfiedRequire();
	}
}
