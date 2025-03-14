// Fill out your copyright notice in the Description page of Project Settings.


#include "Container_Base.h"
#include "../Framework/PlayerCharacterController.h"


UContainer_Base::UContainer_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	//if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	//if (ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;

	//static ConstructorHelpers::FClassFinder<UUserWidget> ItemMoveSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemMoveSlot"));
	//if (ItemMoveSlotFinder.Succeeded()) ItemMoveSlotClass = ItemMoveSlotFinder.Class;
}

void UContainer_Base::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(false);

	//if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemSlotFinder"));
	//if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemBaseFinder"));
	//if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemMoveSlotFinder"));

	//MakeContainer(6, 4);

	//MakeItemToSlot(2, 1, 1);
	//MakeItemToSlot(1, 2, 1);
	//MakeItemToSlot(1, 1, 1);
	//MakeItemToSlot(2, 2, 1);
}

void UContainer_Base::ContainerInitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass,
												EContainerCategory category, float col, float row)
{
	ItemSlotClass = itemSlotClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	MakeContainer(col, row);
	ContainerCategory = category;
}

void UContainer_Base::MakeContainer(int col, int row)
{
	UCanvasPanelSlot* TargetSlot = Cast<UCanvasPanelSlot>(ContainerSlot->Slot);
	TargetSlot->SetSize(FVector2D(ContainerSlotSize * col, ContainerSlotSize * row));

	ContainerSize = FVector2D(col, row);
	ContainerItemSlots.Empty();
	int slotIndex = 0;
	for (int j = 0; j < row; j++) {
		for (int i = 0; i < col; i++) {
			UItemSlot* newItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			SlotInitSetting(newItemSlot->ItemSlot);
			newItemSlot->ContainerPanel = this;
			newItemSlot->SlotIndex = slotIndex++;
			newItemSlot->ItemMoveSlotClass = ItemMoveSlotClass;
			newItemSlot->ItemBaseClass = ItemBaseClass;
			newItemSlot->SlotSize = ContainerSlotSize;
			newItemSlot->SlotColRow = FVector2D(i, j);

			UUniformGridSlot* gridSlot = ContainerSlotGrid->AddChildToUniformGrid(newItemSlot, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);

			ContainerItemSlots.Add(newItemSlot);
		}
	}
}

void UContainer_Base::ResetContainer()
{
	for (UItemSlot* slots : ContainerItemSlots) {
		if (slots->HasItem()) {
			slots->ItemSlot->RemoveChildAt(0);
		}
	}
}

void UContainer_Base::ShowContainer(TArray<FInventoryData*> data)
{
	ResetContainer();
	for (FInventoryData* eachData : data) {
		MakeItemUI(eachData);
		GetContainerSlot(eachData->SlotIndex)->GetSlotItem()->SetItemCountText();
	}
}

void UContainer_Base::MakeItemUI(FInventoryData* data)
{
	TArray<UItemUI_Base*> makingItems;
	for (int i = data->SlotIndex.X; i < data->SlotIndex.X + data->ItemData->width; i++) {
		for (int j = data->SlotIndex.Y; j < data->SlotIndex.Y + data->ItemData->height; j++) {
			UItemSlot* targetSlot = GetContainerSlot(FVector2D(i, j));
			UItemUI_Base* item = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			item->SetItemIndex(FVector2D(i - data->SlotIndex.X, j - data->SlotIndex.Y));
			item->SetItemData(data);

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
}

FVector2D UContainer_Base::MakeItem(UItemData* item, int count)
{
	UItemSlot* targetSlot = HasItem(item, true);
	if (targetSlot) {
		int value = item->maxStack - targetSlot->GetSlotItem()->ItemData->ItemCount;
		if (value < count) {
			targetSlot->GetSlotItem()->ItemData->ItemCount += value;
			MakeItem(item, count - value);
			return targetSlot->SlotColRow;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString(TEXT("Action")));
			targetSlot->GetSlotItem()->ItemData->ItemCount += count;
			return targetSlot->SlotColRow;
		}
	}
	else {
		FVector2D EmptySlot = FindEmptySlot(FVector2D(item->width, item->height));
		if (EmptySlot != FVector2D(-1.0f)) {
			// 찾은 위치에 아이템 생성
			MakeItemUI(new FInventoryData(EmptySlot, item, count));
		}
		return EmptySlot;
	}
}

FVector2D UContainer_Base::MakeItem(FInventoryData* data)
{
	if (data->SlotIndex == FVector2D(-1.0f)) {
		return MakeItem(data->ItemData, data->ItemCount);
	}
	else {
		if (GetContainerSlot(data->SlotIndex)->HasItem()) {
			FInventoryData* targetData = GetContainerSlot(data->SlotIndex)->GetItemData();
			targetData->ItemCount = (targetData->ItemCount + data->ItemCount < data->ItemData->maxStack ? targetData->ItemCount + data->ItemCount : data->ItemData->maxStack);
		}
		else {
			MakeItemUI(data);
		}
		return data->SlotIndex;
	}
}

// to index 쪽에서 실행
void UContainer_Base::MoveItemToSlot(EContainerCategory before, int fromIndex, int toIndex, TArray<UItemUI_Base*> items)
{
	TArray<FVector2D> itemToArea;
	TArray<FVector2D> itemToIndex;

	FVector2D offsetTo = items[0]->ItemIndex;

	// 범위 만들기 (items 의 슬롯에 offset을 빼기)
	for (int i = 0; i < items.Num(); i++) {
		// 실제 인벤토리의 좌표
		itemToArea.Add(ContainerItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo));

		// 인벤토리의 칸을 넘어감
		if (!IsInContainer(itemToArea[i])) return;

		// 해당 칸에 아이템 존재
		UItemSlot* targetSlot = GetContainerSlot(itemToArea[i]);
		if (targetSlot->HasItem()) {
			if (targetSlot->GetSlotItem()->GetOwnerItem() != items[i]->GetOwnerItem()) {
				itemToIndex.Add(itemToArea[i]);
			}
		}
	}

	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	// 안에 아이템이 있으면
	if (itemToIndex.Num() > 0) {
		if (ContainerItemSlots[toIndex]->GetItemData()->ItemData->index == items[0]->ItemData->ItemData->index) {
			if (ContainerCategory == before) {
				TArray<FInventoryData*> targetContainer = controller->PlayerData->GetTargetContainer(ContainerCategory);
				FInventoryData* toData = ContainerItemSlots[toIndex]->GetItemData();
				FInventoryData* fromData = ContainerItemSlots[fromIndex]->GetItemData();

				int value = toData->ItemData->maxStack - toData->ItemCount;
				if (value < fromData->ItemCount) {
					// UI Part
					toData->ItemCount += value;
					fromData->ItemCount -= value;

					// Data Part
					FindContainerSlotData(targetContainer, toData->SlotIndex)->ItemCount = toData->ItemCount;
					FindContainerSlotData(targetContainer, fromData->SlotIndex)->ItemCount = fromData->ItemCount;

					UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
					toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					UItemSlot* fromSlot = GetContainerSlot(ContainerItemSlots[fromIndex]->SlotColRow);
					fromSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
				}
				else {
					// Count 변경 & 기존 아이템 삭제
					targetContainer.Remove(FindContainerSlotData(targetContainer, fromData->SlotIndex));

					toData->ItemCount += fromData->ItemCount;
					FindContainerSlotData(targetContainer, toData->SlotIndex)->ItemCount = toData->ItemCount;

					UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
					toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					UItemSlot* fromSlot = GetContainerSlot(ContainerItemSlots[fromIndex]->SlotColRow);
					fromSlot->GetSlotItem()->GetOwnerItem()->GetParent()->RemoveChildAt(0);
				}
			}
			else {
				TArray<FInventoryData*> ToContainer = controller->PlayerData->GetTargetContainer(ContainerCategory);
				UContainer_Base* ToContainerBase = this;
				TArray<FInventoryData*> FromContainer = controller->PlayerData->GetTargetContainer(before);
				UContainer_Base* FromContainerBase = controller->GetTargetContainer(before);

				FInventoryData* toData = ContainerItemSlots[toIndex]->GetItemData();
				FInventoryData* fromData = FromContainerBase->ContainerItemSlots[fromIndex]->GetItemData();

				int value = toData->ItemData->maxStack - toData->ItemCount;
				if (value < fromData->ItemCount) {
					// UI Part
					toData->ItemCount += value;
					fromData->ItemCount -= value;

					// Data Part
					FindContainerSlotData(ToContainer, toData->SlotIndex)->ItemCount = toData->ItemCount;
					FindContainerSlotData(FromContainer, fromData->SlotIndex)->ItemCount = fromData->ItemCount;

					UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
					toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					UItemSlot* fromSlot = FromContainerBase->GetContainerSlot(FromContainerBase->ContainerItemSlots[fromIndex]->SlotColRow);
					fromSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
				}
				else {
					// Count 변경 & 기존 아이템 삭제
					FromContainer.Remove(FindContainerSlotData(FromContainer, fromData->SlotIndex));

					toData->ItemCount += fromData->ItemCount;
					FindContainerSlotData(ToContainer, toData->SlotIndex)->ItemCount = toData->ItemCount;

					UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
					toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					UItemSlot* fromSlot = FromContainerBase->GetContainerSlot(FromContainerBase->ContainerItemSlots[fromIndex]->SlotColRow);
					fromSlot->GetSlotItem()->GetOwnerItem()->GetParent()->RemoveChildAt(0);
				}
			}
		}
	}
	else { // 안에 아이템이 없으면
		// Data Part
		if (ContainerCategory == before) {
			TArray<FInventoryData*> targetContainer = controller->PlayerData->GetTargetContainer(ContainerCategory);
			FindContainerSlotData(targetContainer, ContainerItemSlots[fromIndex]->SlotColRow)->SlotIndex = ContainerItemSlots[toIndex]->SlotColRow;
		}
		else {
			TArray<FInventoryData*> FromContainer = controller->PlayerData->GetTargetContainer(before);
			UContainer_Base* FromContainerBase = controller->GetTargetContainer(before);
			for (FInventoryData* data : FromContainer) {
				if (data->SlotIndex == FromContainerBase->ContainerItemSlots[fromIndex]->SlotColRow) {
					controller->PlayerData->GetTargetContainer(before).Remove(data);
					data->SlotIndex = ContainerItemSlots[toIndex]->SlotColRow;
					controller->PlayerData->GetTargetContainer(ContainerCategory).Add(data);
					break;
				}
			}
		}

		// UI Part
		for (int i = 0; i < items.Num(); i++) {
			UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo));
			toSlot->ItemSlot->RemoveChildAt(0);
			UButtonSlot* buttonSlot = Cast<UButtonSlot>(toSlot->ItemSlot->AddChild(items[i]));
			buttonSlot->SetPadding(FMargin(0.0f));
			buttonSlot->SetHorizontalAlignment(HAlign_Fill);
			buttonSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

UItemSlot* UContainer_Base::HasItem(UItemData* item, bool checkMax)
{
	for (UItemSlot* target : ContainerItemSlots) {
		if (target->HasItem() && target->GetSlotItem()->ItemData->ItemData->index == item->index) {
			if (checkMax) {
				if (target->GetSlotItem()->ItemData->ItemCount < item->maxStack) {
					return target;
				}
			}
			else {
				return target;
			}
			break;
		}
	}

	return nullptr;
}

FVector2D UContainer_Base::FindEmptySlot(FVector2D size)
{
	// 빈 위치 찾기
	int col = 0; int row = 0;
	bool bFindSlot = false;
	for (int i = 0; i < ContainerItemSlots.Num(); i++) {
		if (ContainerItemSlots[i]->HasItem()) continue;

		FVector2D slotColRow = ContainerItemSlots[i]->SlotColRow;
		bFindSlot = true;

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%.1f")));

		for (int j = 0; j < size.X; j++) {
			for (int k = 0; k < size.Y; k++) {
				FVector2D TargetColRow = FVector2D(slotColRow.X + j, slotColRow.Y + k);

				if (!IsInContainer(TargetColRow)) {
					bFindSlot = false;
					break;
				}

				if (GetContainerSlot(TargetColRow)->HasItem()) {
					bFindSlot = false;
					break;
				}
			}
			if (!bFindSlot) break;
		}

		if (bFindSlot) {
			col = slotColRow.X; row = slotColRow.Y;
			return FVector2D(col, row);
			break;
		}
	}

	return FVector2D(-1, -1);
}

FInventoryData* UContainer_Base::FindContainerSlotData(TArray<FInventoryData*>& data, FVector2D slotIndex)
{
	for (FInventoryData* inData : data) {
		if (inData->SlotIndex == slotIndex) {
			return inData;
		}
	}
	return nullptr;
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
	button->IsFocusable = false;
}

UItemSlot* UContainer_Base::GetContainerSlot(FVector2D index)
{
	int col = index.X; int row = index.Y;

	for (int i = 0; i < ContainerItemSlots.Num(); i++) {
		if (ContainerItemSlots[i]->SlotColRow == index) {
			return ContainerItemSlots[i];
		}
	}

	return nullptr;
}