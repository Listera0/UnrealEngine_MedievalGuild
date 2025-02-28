// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"


UPlayerInventory::UPlayerInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	if(ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemMoveSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemMoveSlot"));
	if (ItemMoveSlotFinder.Succeeded()) ItemMoveSlotClass = ItemMoveSlotFinder.Class;
}

void UPlayerInventory::NativeConstruct()
{
	if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemSlotFinder"));
	if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemBaseFinder"));
	if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemMoveSlotFinder"));

	MakeInventory(2, 3);

	MakeItemToSlot(0, 0, 1, 1, 1);
	MakeItemToSlot(0, 1, 2, 1, 2);
}

void UPlayerInventory::MakeInventory(int col, int row)
{
	UCanvasPanelSlot* inventorySlot = Cast<UCanvasPanelSlot>(InventorySlot->Slot);
	inventorySlot->SetSize(FVector2D(InventorySlotSize * col, InventorySlotSize * row));

	InventorySize = FVector2D(col, row);
	ItemSlots.Empty();
	int slotIndex = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			UItemSlot* newItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			SlotInitSetting(newItemSlot->ItemSlot);
			newItemSlot->InventoryPanel = this;
			newItemSlot->SlotIndex = slotIndex++;
			newItemSlot->ItemMoveSlotClass = ItemMoveSlotClass;
			newItemSlot->ItemBaseClass = ItemBaseClass;
			newItemSlot->SlotSize = InventorySlotSize;
			newItemSlot->SlotColRow = FVector2D(i, j);

			UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newItemSlot, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);

			ItemSlots.Add(newItemSlot);
		}
	}
}

void UPlayerInventory::MakeItemToSlot(int col, int row, int sizeX, int sizeY, int count)
{
	TArray<UItemUI_Base*> makingItems;
	for (int i = col; i < col + sizeX; i++) {
		for (int j = row; j < row + sizeY; j++) {
			UItemSlot* targetSlot = Cast<UItemSlot>(GetInventorySlot(i, j));
			UItemUI_Base* item = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			item->SetItemIndex(i - col, j - row);
			item->SetItemSize(sizeX, sizeY);

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

	makingItems.Last()->SetItemCount(count);
}

void UPlayerInventory::MoveItemToSlot(int fromIndex, int toIndex, TArray<UItemUI_Base*> items)
{
	FVector2D ColRow = ItemSlots[toIndex]->SlotColRow;

	/*
	ㅁㅁ
	ㅁㅁ
	ㅁㅁ
	ㅎㅎ
	*/


	// 1. 범위 가져오기, 두 범위다 상정범위내에 있다면
	// 2. 범위 내에 어떠한 아이템도 없을 때
	// 3. 범위 내에 어떠한 아이템이 있을 때

	for (int i = 0; i < items.Num(); i++) {
		FVector2D Index = FVector2D(items[i]->ItemIndexX, items[i]->ItemIndexY);
		UItemSlot* toSlot = GetInventorySlot2(ColRow.X + Index.X, ColRow.Y + Index.Y);
		UButtonSlot* buttonSlot = Cast<UButtonSlot>(toSlot->ItemSlot->AddChild(items[i]));
		buttonSlot->SetPadding(FMargin(0.0f));
		buttonSlot->SetHorizontalAlignment(HAlign_Fill);
		buttonSlot->SetVerticalAlignment(VAlign_Fill);
	}
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

UItemSlot* UPlayerInventory::GetInventorySlot2(int col, int row)
{
	for (int i = 0; i < ItemSlots.Num(); i++) {
		if ((int)(ItemSlots[i]->SlotColRow.X) == col && (int)(ItemSlots[i]->SlotColRow.Y) == row) {
			return ItemSlots[i];
		}
	}
	return nullptr;
}