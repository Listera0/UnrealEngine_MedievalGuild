// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"


void UPlayerInventory::NativeConstruct()
{
	MakeInventory(2, 3);
}

void UPlayerInventory::MakeInventory(int col, int row)
{
	if (!SlotGridPanel)
		return;

	UCanvasPanelSlot* inventorySlot = Cast<UCanvasPanelSlot>(InventorySlot->Slot);
	inventorySlot->SetSize(FVector2D(InventorySlotSize * col, InventorySlotSize * row));

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			UButton* newButton = NewObject<UButton>(this);
			SlotInitSetting(newButton);
			UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newButton, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UPlayerInventory::MakeItemToSlot(int col, int row)
{
	
}

void UPlayerInventory::SlotInitSetting(UButton* button)
{
	//FButtonStyle buttonStyle = button->GetStyle();

	//buttonStyle.Normal.DrawAs = ESlateBrushDrawType::Box;
	//buttonStyle.Hovered.DrawAs = ESlateBrushDrawType::Box;
	//buttonStyle.Pressed.DrawAs = ESlateBrushDrawType::Box;

	//buttonStyle.Normal.TintColor = FSlateColor(FColor(0.2f, 0.2f, 0.2f, 1.0f));
	//buttonStyle.Hovered.TintColor = FSlateColor(FColor(0.2f, 0.2f, 0.2f, 1.0f));
	//buttonStyle.Pressed.TintColor = FSlateColor(FColor(0.2f, 0.2f, 0.2f, 1.0f));

	//buttonStyle.NormalPadding = 0.0f;
	//buttonStyle.PressedPadding = 0.0f;

	//button->SetStyle(buttonStyle);
}
