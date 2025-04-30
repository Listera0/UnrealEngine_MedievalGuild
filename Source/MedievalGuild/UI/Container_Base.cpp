// Fill out your copyright notice in the Description page of Project Settings.


#include "Container_Base.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/GameUserSettings.h"


UContainer_Base::UContainer_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UContainer_Base::NativeConstruct()
{
	Super::NativeConstruct();

}

void UContainer_Base::ContainerInitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass,
											TSubclassOf<UUserWidget> itemSlotImgClass, EContainerCategory category, FVector2D size)
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	ItemSlotClass = itemSlotClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	ItemSlotImgClass = itemSlotImgClass;
	ContainerCategory = category;
	MakeContainer(size);
}

void UContainer_Base::MakeContainer(FVector2D size)
{
	ContainerSlotSize = (((float)(PlayerController->SizeX) / 3.0f - (75.0f * PlayerController->ViewportScale.X)) / 6.0f) / PlayerController->ViewportScale.X;
	ContainerSize = size;

	UCanvasPanelSlot* TargetSlot = Cast<UCanvasPanelSlot>(ContainerSlot->Slot);
	TargetSlot->SetSize(ContainerSlotSize * size);

	ContainerItemSlots.Empty();
	int slotIndex = 0;
	for (int j = 0; j < (int)(size.Y); j++) {
		for (int i = 0; i < (int)(size.X); i++) {
			UItemSlot* newItemSlot = CreateWidget<UItemSlot>(GetWorld(), ItemSlotClass);
			UItemSlotImg* newItemSlotImg = CreateWidget<UItemSlotImg>(GetWorld(), ItemSlotImgClass);
			SlotInitSetting(newItemSlot->ItemSlot);
			SlotInitSetting(newItemSlotImg->ItemSlot);
			newItemSlot->ContainerPanel = this;
			newItemSlot->SlotIndex = slotIndex++;
			newItemSlot->ItemMoveSlotClass = ItemMoveSlotClass;
			newItemSlot->ItemBaseClass = ItemBaseClass;
			newItemSlot->SlotSize = ContainerSlotSize;
			newItemSlot->SlotColRow = FVector2D(i, j);

			UUniformGridSlot* gridSlot = ContainerSlotGrid->AddChildToUniformGrid(newItemSlot, j, i);
			UUniformGridSlot* gridImgSlot = ContainerSlotImgGrid->AddChildToUniformGrid(newItemSlotImg, j, i);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
			gridImgSlot->SetHorizontalAlignment(HAlign_Fill);
			gridImgSlot->SetVerticalAlignment(VAlign_Fill);

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

void UContainer_Base::ShowContainer(TArray<FInventoryData*>& data)
{
	ResetContainer();
	for (FInventoryData* eachData : data) {
		MakeItemUI(eachData);
		GetContainerSlot(eachData->SlotIndex)->GetSlotItem()->SetItemCountText();
	}
}

void UContainer_Base::ShowContainer(FInventoryData* data)
{
	ResetContainer();
	if (data) {
		MakeItemUI(data);
		GetContainerSlot(data->SlotIndex)->GetSlotItem()->SetItemCountText();
	}
}

void UContainer_Base::MakeItemUI(FInventoryData* data)
{
	TArray<UItemUI_Base*> makingItems;
	for (int i = data->SlotIndex.X; i < data->SlotIndex.X + data->ItemData->width; i++) {
		for (int j = data->SlotIndex.Y; j < data->SlotIndex.Y + data->ItemData->height; j++) {
			UItemUI_Base* item = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			item->SetItemIndex(FVector2D(i - data->SlotIndex.X, j - data->SlotIndex.Y));
			item->SetItemData(data);
			item->SetItemImage(data->ItemData, item->ItemIndex);

			if (item == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "no item ui");
				break;
			}

			UItemSlot* targetSlot = GetContainerSlot(FVector2D(i, j));
			if (targetSlot == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "no target slot");
				break;
			}
			UButtonSlot* buttonSlot = Cast<UButtonSlot>(targetSlot->ItemSlot->AddChild(item));
			if (buttonSlot == nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, FString::Printf(TEXT("%d : %d"), i, j));
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, "no button slot");
				break;
			}
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

FVector2D UContainer_Base::MakeItem(FInventoryData* data)
{
	if (data->SlotIndex == FVector2D(-1.0f)) {
		UItemSlot* targetSlot = HasItem(data->ItemData, true);
		if (targetSlot) {
			int value = data->ItemData->maxStack - targetSlot->GetItemData()->ItemCount;
			if (value < data->ItemCount) {
				targetSlot->GetItemData()->ItemCount += value;
				data->ItemCount -= value;
				MakeItem(data);
			}
			else {
				targetSlot->GetItemData()->ItemCount += data->ItemCount;
			}
		}
		else {
			FVector2D EmptySlot = FindEmptySlot(FVector2D(data->ItemData->width, data->ItemData->height));
			if (EmptySlot != FVector2D(-1.0f)) {
				data->SlotIndex = EmptySlot;
				MakeItemUI(data);
			}
		}
	}
	else {
		if (GetContainerSlot(data->SlotIndex)->HasItem()) {
			FInventoryData* targetData = GetContainerSlot(data->SlotIndex)->GetItemData();
			if (targetData->ItemData->index == data->ItemData->index) {
				(targetData->ItemCount + data->ItemCount < data->ItemData->maxStack) ? targetData->ItemCount += data->ItemCount : targetData->ItemCount = data->ItemData->maxStack;
				GetContainerSlot(targetData->SlotIndex)->GetSlotItem()->SetItemCountText();
			}
		}
		else {
			MakeItemUI(data);
		}
	}

	return data->SlotIndex;
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

	// 안에 아이템이 있으면
	if (itemToIndex.Num() > 0) {
		if (ContainerItemSlots[toIndex]->HasItem()) {
			if (ContainerItemSlots[toIndex]->GetItemData()->ItemData->index == items[0]->ItemData->ItemData->index) {
				// 같은 아이템 && 같은 컨테이너일 경우
				if (ContainerCategory == before) {
					TArray<FInventoryData*>& targetContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
					FInventoryData* toData = ContainerItemSlots[toIndex]->GetItemData();
					FInventoryData* fromData = ContainerItemSlots[fromIndex]->GetItemData();

					int value = toData->ItemData->maxStack - toData->ItemCount;
					if (value < fromData->ItemCount) {
						toData->ItemCount += value;
						fromData->ItemCount -= value;

						UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
						toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
						UItemSlot* fromSlot = GetContainerSlot(ContainerItemSlots[fromIndex]->SlotColRow);
						fromSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					}
					else {
						toData->ItemCount += fromData->ItemCount;
						targetContainer.Remove(fromData);

						UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
						toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();

						UItemSlot* fromSlot = GetContainerSlot(ContainerItemSlots[fromIndex]->SlotColRow);
						fromSlot->RemoveItem();
					}
				}
				// 같은 아이템 && 다른 컨테이너일 경우
				else {
					TArray<FInventoryData*>& ToContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
					TArray<FInventoryData*>& FromContainer = PlayerController->PlayerData->GetTargetContainer(before);
					UContainer_Base* FromContainerBase = PlayerController->GetTargetContainer(before);

					FInventoryData* toData = ContainerItemSlots[toIndex]->GetItemData();
					FInventoryData* fromData = FromContainerBase->ContainerItemSlots[fromIndex]->GetItemData();

					int value = toData->ItemData->maxStack - toData->ItemCount;
					if (value < fromData->ItemCount) {
						toData->ItemCount += value;
						fromData->ItemCount -= value;

						UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
						toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
						UItemSlot* fromSlot = FromContainerBase->GetContainerSlot(FromContainerBase->ContainerItemSlots[fromIndex]->SlotColRow);
						fromSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();
					}
					else {
						toData->ItemCount += fromData->ItemCount;
						FromContainer.Remove(fromData);

						UItemSlot* toSlot = GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow);
						toSlot->GetSlotItem()->GetOwnerItem()->SetItemCountText();

						UItemSlot* fromSlot = FromContainerBase->GetContainerSlot(ContainerItemSlots[fromIndex]->SlotColRow);
						fromSlot->RemoveItem();
					}
				}
			}
		}
	}
	else { // 안에 아이템이 없으면
		// 같은 컨테이너일 경우
		if (ContainerCategory == before) {
			TArray<FInventoryData*>& targetContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
			FInventoryData* fromData = ContainerItemSlots[fromIndex]->GetItemData();
			fromData->SlotIndex = ContainerItemSlots[toIndex]->SlotColRow - offsetTo;

			ShowContainer(targetContainer);
		}
		else { // 다른 컨테이너일 경우
			TArray<FInventoryData*>& ToContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
			TArray<FInventoryData*>& FromContainer = PlayerController->PlayerData->GetTargetContainer(before);
			UContainer_Base* FromContainerBase = PlayerController->GetTargetContainer(before);

			FInventoryData* fromData = FromContainerBase->ContainerItemSlots[fromIndex]->GetItemData();
			FromContainer.Remove(fromData);
			fromData->SlotIndex = ContainerItemSlots[toIndex]->SlotColRow - offsetTo;
			ToContainer.Add(fromData);

			ShowContainer(ToContainer);
			FromContainerBase->ShowContainer(FromContainer);
		}
	}
}

void UContainer_Base::MoveItemToSlot(EContainerCategory before, FInventoryData* itemData)
{
	if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	TArray<FInventoryData*>& FromContainer = PlayerController->PlayerData->GetTargetContainer(before);
	TArray<FInventoryData*>& ToContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
	int typeIndex = GetEquipmentIndex(itemData->ItemData->eItemType);

	FromContainer.Remove(itemData);
	itemData->SlotIndex = FVector2D(0.0f, 0.0f);
	ToContainer[typeIndex] = itemData;

	PlayerController->GetTargetContainer(before)->ShowContainer(FromContainer);
	ShowContainer(ToContainer[typeIndex]);
}

void UContainer_Base::MoveItemToSlot(int equipIndex, int toIndex, TArray<UItemUI_Base*> items)
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	FInventoryData* fromData = PlayerController->PlayerData->PlayerEquipment[equipIndex];

	// 잡고있는 아이템 오프셋 을 기준으로 칸이 비어있는지 확인
	FVector2D offsetTo = items[0]->ItemIndex;
	for (int i = 0; i < items.Num(); i++) {
		// 인벤토리의 칸을 넘어감
		if (!IsInContainer(ContainerItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo))) return;
		// 해당 칸에 아이템 존재
		if (GetContainerSlot(ContainerItemSlots[toIndex]->SlotColRow + (items[i]->ItemIndex - offsetTo))->HasItem()) return;
	}

	fromData->SlotIndex = ContainerItemSlots[toIndex]->SlotColRow - offsetTo;
	TArray<FInventoryData*>& ToContainer = PlayerController->PlayerData->GetTargetContainer(ContainerCategory);
	ToContainer.Add(fromData);
	ShowContainer(ToContainer);
	PlayerController->PlayerData->PlayerEquipment[equipIndex] = nullptr;
}


UItemSlot* UContainer_Base::HasItem(UItemData* item, bool checkMax)
{
	if (ContainerItemSlots.Num() < 1) {
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, TEXT("no slots"));
		return nullptr;
	}

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
	bool bFindSlot = false;
	for (int i = 0; i < ContainerItemSlots.Num(); i++) {
		if (ContainerItemSlots[i]->HasItem()) continue;
		//if(controller->PlayerData->GetTargetContainer(ContainerCategory))

		FVector2D slotColRow = ContainerItemSlots[i]->SlotColRow;

		bFindSlot = true;
		for (int j = 0; j < size.X; j++) {
			for (int k = 0; k < size.Y; k++) {
				FVector2D TargetColRow = ContainerItemSlots[i]->SlotColRow + FVector2D(j, k);

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

		if (bFindSlot) { return slotColRow; }
	}

	return FVector2D(-1.0f);
}

FInventoryData* UContainer_Base::FindContainerSlotData(TArray<FInventoryData*>& data, FVector2D slotIndex)
{
	for (FInventoryData* inData : data) {
		if (inData->SlotIndex == slotIndex) {
			return inData;
			break;
		}
	}
	return nullptr;
}

void UContainer_Base::SlotInitSetting(UButton* button)
{
	FButtonStyle buttonStyle;
	FSlateBrush borderBrush;

	borderBrush.TintColor = FLinearColor(0.2f, 0.2f, 0.2f, 0.0f);
	borderBrush.DrawAs = ESlateBrushDrawType::Box;

	buttonStyle.SetNormal(borderBrush);
	buttonStyle.SetHovered(borderBrush);
	buttonStyle.SetPressed(borderBrush);

	buttonStyle.NormalPadding = 0.0f;
	buttonStyle.PressedPadding = 0.0f;

	button->SetStyle(buttonStyle);
}

void UContainer_Base::SlotInitSetting(UImage* image)
{
	image->SetColorAndOpacity(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f));
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

int UContainer_Base::GetEquipmentIndex(EItemType type)
{
	int returnValue = 0;

	switch (type)
	{
	case EItemType::Helmet:
		returnValue = 0;
		break;
	case EItemType::Cloth:
		returnValue = 1;
		break;
	case EItemType::Shoes:
		returnValue = 2;
		break;
	case EItemType::Bag:
		returnValue = 3;
		break;
	case EItemType::Weapon:
		returnValue = 4;
		break;
	}

	return returnValue;
}
