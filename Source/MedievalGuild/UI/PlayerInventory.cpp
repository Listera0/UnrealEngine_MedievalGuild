// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"


UPlayerInventory::UPlayerInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	if(ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;
}

void UPlayerInventory::NativeConstruct()
{
	if (ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Loaded ItemSlotFinder"));
	if (ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Loaded ItemBaseFinder"));

	MakeInventory(2, 3);

	MakeItemToSlot(0, 0, 1, 1, 1);
	MakeItemToSlot(0, 1, 2, 1, 2);
}

void UPlayerInventory::MakeInventory(int col, int row)
{
	UCanvasPanelSlot* inventorySlot = Cast<UCanvasPanelSlot>(InventorySlot->Slot);
	inventorySlot->SetSize(FVector2D(InventorySlotSize * col, InventorySlotSize * row));

	int slotIndex = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			UItemSlot* newItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			SlotInitSetting(newItemSlot->ItemSlot);
			newItemSlot->SlotIndex = slotIndex++;

			UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newItemSlot, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UPlayerInventory::MakeItemToSlot(int col, int row, int sizeX, int sizeY, int count)
{
	TArray<UItemUI_Base*> makingItems;
	for (int i = col; i < col + sizeY; i++) {
		for (int j = row; j < row + sizeX; j++) {
			UItemSlot* targetSlot = Cast<UItemSlot>(GetInventorySlot(i, j));
			UItemUI_Base* item = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);

			UButtonSlot* buttonSlot = Cast<UButtonSlot>(targetSlot->ItemSlot->AddChild(item));
			buttonSlot->SetPadding(FMargin(0.0f));
			buttonSlot->SetHorizontalAlignment(HAlign_Fill);
			buttonSlot->SetVerticalAlignment(VAlign_Fill);

			makingItems.Add(item);
		}
	}

	TArray<UItemUI_Base*> tempItems;
	for (int i = 0; i < makingItems.Num(); i++) {
		tempItems.Empty();
		for (int j = 0; j < makingItems.Num(); j++) {
			if (i != j) {
				tempItems.Add(makingItems[j]);
			}
		}
		makingItems[i]->SetItemBind(tempItems);
	}

	makingItems.Last()->bStackable = true;
	makingItems.Last()->ItemCount = count;
	makingItems.Last()->SetItemCountText();
}

void UPlayerInventory::MoveItemToSlot(int fromCol, int fromRow, int toCol, int toRow)
{

}

void UPlayerInventory::SlotInitSetting(UButton* button)
{
	FButtonStyle buttonStyle;
	FSlateBrush borderBrush;

	borderBrush.TintColor = FLinearColor(0.2f, 0.2f, 0.2f, 1.0f);
	borderBrush.DrawAs = ESlateBrushDrawType::Box;
	//borderBrush.DrawAs = ESlateBrushDrawType::Border;
	//borderBrush.Margin = FMargin(0.5f);

	buttonStyle.SetNormal(borderBrush);
	buttonStyle.SetHovered(borderBrush);
	buttonStyle.SetPressed(borderBrush);

	buttonStyle.NormalPadding = 0.0f;
	buttonStyle.PressedPadding = 0.0f;

	button->SetStyle(buttonStyle);	
}

UWidget* UPlayerInventory::GetInventorySlot(int col, int row)
{
	for (UWidget* slot : SlotGridPanel->GetAllChildren()) {
		if (UUniformGridSlot* targetSlot = Cast<UUniformGridSlot>(slot->Slot)) {
			if (targetSlot->GetColumn() == col && targetSlot->GetRow() == row) {
				return slot;
			}
		}
	}
	return nullptr;
}