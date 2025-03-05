// Fill out your copyright notice in the Description page of Project Settings.


#include "Container_Base.h"


UContainer_Base::UContainer_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	if (ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemMoveSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemMoveSlot"));
	if (ItemMoveSlotFinder.Succeeded()) ItemMoveSlotClass = ItemMoveSlotFinder.Class;
}

void UContainer_Base::NativeConstruct()
{
	if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemSlotFinder"));
	if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemBaseFinder"));
	if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemMoveSlotFinder"));

	MakeContainer(3, 4);

	MakeItemToSlot(0, 0, 1, 1, 1);
	MakeItemToSlot(0, 1, 2, 1, 2);
	MakeItemToSlot(2, 2, 2);
}

void UContainer_Base::MakeContainer(int col, int row)
{
	UCanvasPanelSlot* inventorySlot = Cast<UCanvasPanelSlot>(ContainerSlot->Slot);
	inventorySlot->SetSize(FVector2D(ContainerSlotSize * col, ContainerSlotSize * row));

	ContainerSize = FVector2D(col, row);
	ItemSlots.Empty();
	int slotIndex = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			UItemSlot* newItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			SlotInitSetting(newItemSlot->ItemSlot);
			newItemSlot->ContainerPanel = this;
			newItemSlot->SlotIndex = slotIndex++;
			newItemSlot->ItemMoveSlotClass = ItemMoveSlotClass;
			newItemSlot->ItemBaseClass = ItemBaseClass;
			newItemSlot->SlotSize = ContainerSlotSize;
			newItemSlot->SlotColRow = FVector2D(i, j);

			UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newItemSlot, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);

			ItemSlots.Add(newItemSlot);
		}
	}
}

void UContainer_Base::MakeItemToSlot(int col, int row, int sizeX, int sizeY, int count)
{
	TArray<UItemUI_Base*> makingItems;
	for (int i = col; i < col + sizeX; i++) {
		for (int j = row; j < row + sizeY; j++) {
			UItemSlot* targetSlot = GetContainerSlot(i, j);
			UItemUI_Base* item = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			item->SetItemIndex(FVector2D(i - col, j - row));
			item->SetItemSize(FVector2D(sizeX, sizeY));

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

void UContainer_Base::MakeItemToSlot(int sizeX, int sizeY, int count)
{
	// 빈 위치 찾기
	int col = 0; int row = 0;
	bool bFindSlot = false;
	for (int i = 0; i < ItemSlots.Num(); i++) {
		if (ItemSlots[i]->HasItem()) continue;

		FVector2D slotColRow = ItemSlots[i]->SlotColRow;
		bFindSlot = true;

		for (int j = 0; j < sizeX; j++) {
			for (int k = 0; k < sizeY; k++) {
				if (!IsInContainer(FVector2D(slotColRow.X + j, slotColRow.Y + k))) {
					bFindSlot = false;
					break;
				}

				if (GetContainerSlot(slotColRow.X + j, slotColRow.Y + k)->HasItem()) {
					bFindSlot = false;
					break;
				}
			}
			if (!bFindSlot) break;
		}

		if (bFindSlot) {
			col = slotColRow.X; row = slotColRow.Y;
			break;
		}
	}

	if (bFindSlot) {
		// 찾은 위치에 아이템 생성
		MakeItemToSlot(col, row, sizeX, sizeY, count);
	}
}

void UContainer_Base::MoveItemToSlot(int fromIndex, int toIndex, TArray<UItemUI_Base*> items)
{
	TArray<FVector2D> itemToArea;
	TArray<FVector2D> itemToIndex;

	FVector2D offsetTo = items[0]->ItemIndex;

	// 범위 만들기 (items 의 슬롯에 offset을 빼기)
	for (int i = 0; i < items.Num(); i++) {
		// 실제 인벤토리의 좌표
		itemToArea.Add(ItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo));

		// 인벤토리의 칸을 넘어감
		if (!IsInContainer(itemToArea[i])) return;

		// 해당 칸에 아이템 존재
		UItemSlot* targetSlot = GetContainerSlot(itemToArea[i]);
		if (targetSlot->HasItem()) {
			if (targetSlot->GetSlotItem()->GetOwnerItem() != items[i]->GetOwnerItem()) {
				itemToIndex.Add(itemToArea[i]);
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("Has Item")));
			}
		}
	}

	// 안에 아이템이 있으면
	if (itemToIndex.Num() > 0) {
		//TArray<UItemUI_Base*> toItems;
		//TArray<FVector2D> itemFromArea;

		//for (int i = 0; i < itemToIndex.Num(); i++) {
		//	toItems.AddUnique(GetInventorySlot(itemToIndex[i])->GetSlotItem()->GetOwnerItem());
		//}

		//// 연결된 모든 아이템 이동 필요

		//for (int i = 0; i < toItems.Num(); i++) {
		//	FVector2D offsetFrom = toItems[i]->ItemIndex;
		//	
		//	fromIndex - (toItems[i]->ItemIndex - ItemSlots[toIndex]->SlotColRow) + index;
		//}

		//itemFromArea.Add(ItemSlots[fromIndex]->SlotColRow + (items[i]->ItemIndex - offsetFrom));

	}
	else { // 안에 아이템이 없으면
		for (int i = 0; i < items.Num(); i++) {
			FVector2D Index = items[i]->ItemIndex;
			UItemSlot* toSlot = GetContainerSlot(ItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo));
			toSlot->ItemSlot->RemoveChildAt(0);
			UButtonSlot* buttonSlot = Cast<UButtonSlot>(toSlot->ItemSlot->AddChild(items[i]));
			buttonSlot->SetPadding(FMargin(0.0f));
			buttonSlot->SetHorizontalAlignment(HAlign_Fill);
			buttonSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UContainer_Base::SlotInitSetting(UButton* button)
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

UItemSlot* UContainer_Base::GetContainerSlot(int col, int row)
{
	for (int i = 0; i < ItemSlots.Num(); i++) {
		if ((int)(ItemSlots[i]->SlotColRow.X) == col && (int)(ItemSlots[i]->SlotColRow.Y) == row) {
			return ItemSlots[i];
		}
	}
	return nullptr;
}

UItemSlot* UContainer_Base::GetContainerSlot(FVector2D index)
{
	int col = index.X; int row = index.Y;

	for (int i = 0; i < ItemSlots.Num(); i++) {
		if ((int)(ItemSlots[i]->SlotColRow.X) == col && (int)(ItemSlots[i]->SlotColRow.Y) == row) {
			return ItemSlots[i];
		}
	}

	return nullptr;
}
