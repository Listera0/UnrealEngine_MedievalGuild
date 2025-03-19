// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "Container_Base.h"
#include "../Framework/PlayerCharacterController.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(false);
}

FReply UItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		if (HasItem()) {
			if (ContainerPanel->ContainerCategory == EContainerCategory::Merchant) {
				if (PlayerController->InventoryUI->Widget_Trade->bIsSell) { goto PassOnClick; }
				else {
					PlayerController->InventoryUI->Widget_Trade->SelectBuyItem(GetItemData());
				}
			}
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Trade) {
				if (PlayerController->InventoryUI->Widget_Trade->bIsBuy) {
					PlayerController->InventoryUI->Widget_Trade->SelectBuyItem(nullptr);
				}
				else {
					if (PlayerController->IsShiftPressed()) { SlotButtonShiftClick(); }
					else { Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton); }
				}
			}
			else {
				if (PlayerController->IsShiftPressed()) { SlotButtonShiftClick(); }
				else { Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton); }
			}
		}
	}

	PassOnClick:
	return Reply.NativeReply;
}

void UItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr) {
		UItemDragDropOperation* Operation = NewObject<UItemDragDropOperation>();
		OutOperation = Operation;

		// 드래그용 슬롯 만들기
		UItemMoveSlot* dragSlot = CreateWidget<UItemMoveSlot>(GetWorld(), ItemMoveSlotClass);

		// 연결된 아이템들 가져오기
		TArray<UItemUI_Base*> movingItems;
		movingItems.Add(Cast<UItemUI_Base>(ItemSlot->GetChildAt(0)));
		movingItems.Append(movingItems[0]->BindItems);

		// 드래그한 그 아이템정보 저장 및 슬롯 크기 변경
		FVector2D itemIndex = movingItems[0]->ItemIndex;
		FVector2D itemSize = FVector2D(movingItems[0]->ItemData->ItemData->width, movingItems[0]->ItemData->ItemData->height);
		dragSlot->InitSetting(SlotSize * itemSize);

		// 가져온 모든 아이템들 복제본 만들어 슬롯에 넣기
		for (int i = 0; i < movingItems.Num(); i++) {
			UItemUI_Base* draggingItem = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			draggingItem->SetItemData(movingItems[i]->ItemData);
			movingItems[i]->SetVisibility(ESlateVisibility::Collapsed);

			UUniformGridSlot* gridSlot = dragSlot->MovingSlot->AddChildToUniformGrid(draggingItem, draggingItem->ItemIndex.X, draggingItem->ItemIndex.Y);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}

		movingItems[0]->SetItemCountText();
		FVector2D CustomOffset = (itemIndex - ((itemSize - 1) * 0.5f)) * -SlotSize;
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(dragSlot->MovingSlot->Slot);
		canvasSlot->SetPosition(CustomOffset);

		Operation->PrevContainerCategory = ContainerPanel->ContainerCategory;
		Operation->PrevSlotOwner = GetOuter();
		Operation->PrevSlotIndex = SlotIndex;
		Operation->bMoveSuccessed = false;
		Operation->SetOrigianlWidgets(movingItems);
		Operation->DefaultDragVisual = dragSlot;
	}
}

void UItemSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UItemDragDropOperation* Operation = Cast<UItemDragDropOperation>(InOperation);

	if (Operation) {
		for (int i = 0; i < Operation->OriginalWidgets.Num(); i++) {
			Operation->OriginalWidgets[i]->SetVisibility(ESlateVisibility::Visible);
		}

		if (!Operation->bMoveSuccessed) {
			// Turn back action
		}
	}
}

bool UItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!InOperation) return false;
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	UItemDragDropOperation* Operation = Cast<UItemDragDropOperation>(InOperation);
	if (Operation) {
		if (Operation->OriginalWidgets[0] != GetSlotItem()) {
			UItemUI_Base* ownerItem = Operation->OriginalWidgets[0]->GetOwnerItem();
			EContainerCategory before = Operation->PrevContainerCategory;

			if (ContainerPanel->ContainerCategory == EContainerCategory::Merchant) { return false; }
			else if (before == EContainerCategory::Trade) {
				UTradeWidget* tradeWidget = PlayerController->InventoryUI->Widget_Trade;
				if (tradeWidget->bIsBuy) { return false; }
				if (tradeWidget->bIsSell) { 
					ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
				}
			}
			else if (PlayerController->PlayerData->GetEquipmentIndex(ContainerPanel->ContainerCategory) != -1) {
				if (HasItem()) { return false; }
				int containerTypeIndex = GetEquipmentIndex(ownerItem->ItemData->ItemData->eItemType);
				if (containerTypeIndex == -1) return false;
				if (containerTypeIndex != PlayerController->PlayerData->GetEquipmentIndex(ContainerPanel->ContainerCategory)) { return false; }

				ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, ownerItem->ItemData);
			}
			else {
				ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
			}

			if (before == EContainerCategory::Trade) {
				PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
			}

			if (ContainerPanel->ContainerCategory == EContainerCategory::Trade) {
				PlayerController->InventoryUI->Widget_Trade->bIsSell = true;
				PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
			}

			Operation->bMoveSuccessed = true;
		}
	}

	return false;
}

int UItemSlot::GetEquipmentIndex(EItemType itemType)
{
	int returnValue = -1;

	switch (itemType) {
		case EItemType::Helmet: returnValue = 0; break;
		case EItemType::Cloth: returnValue = 1; break;
		case EItemType::Shoes: returnValue = 2; break;
		case EItemType::Bag: returnValue = 3; break;
		case EItemType::Weapon: returnValue = 4; break;
	}

	return returnValue;
}

void UItemSlot::RemoveItem()
{
	UItemUI_Base* ownerItem = GetSlotItem()->GetOwnerItem();

	for (UItemUI_Base* target : ownerItem->BindItems) {
		target->GetParent()->RemoveChildAt(0);
	}
	ownerItem->GetParent()->RemoveChildAt(0);
}

void UItemSlot::SlotButtonShiftClick()
{
	if (PlayerController->IsInteractAction()) {
		UContainer_Base* otherContainer = nullptr;
		EContainerCategory otherCategory = EContainerCategory::None;

		if (PlayerController->InteractObj->ActorHasTag(FName("Container"))) {
			if (ContainerPanel->ContainerCategory == EContainerCategory::Inventory) { otherCategory = EContainerCategory::Container; }
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Container) { otherCategory = EContainerCategory::Inventory; }
		}
		else if (PlayerController->InteractObj->ActorHasTag(FName("Storage"))) {
			if (ContainerPanel->ContainerCategory == EContainerCategory::Inventory) { otherCategory = EContainerCategory::Storage; }
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Storage) { otherCategory = EContainerCategory::Inventory; }
		}
		else if (PlayerController->InteractObj->ActorHasTag(FName("Merchant"))) {
			if (ContainerPanel->ContainerCategory == EContainerCategory::Storage) { otherCategory = EContainerCategory::Trade; }
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Merchant) { otherCategory = EContainerCategory::Trade; }
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Trade) {
				if (PlayerController->InventoryUI->Widget_Trade->bIsBuy) { otherCategory = EContainerCategory::Merchant; }
				else if (PlayerController->InventoryUI->Widget_Trade->bIsSell) { otherCategory = EContainerCategory::Storage; }
				else return;
			}
		}
		else return;

		otherContainer = PlayerController->GetTargetContainer(otherCategory);

		FInventoryData* itemInfo = GetSlotItem()->GetOwnerItem()->ItemData;
		FVector2D itemSize(itemInfo->ItemData->width, itemInfo->ItemData->height);
		int itemMaxStack = itemInfo->ItemData->maxStack;

		while (itemInfo->ItemCount > 0) {
			UItemSlot* targetSlot = otherContainer->HasItem(itemInfo->ItemData, true);
			if (targetSlot) {
				int value = itemMaxStack - targetSlot->GetItemData()->ItemCount;
				if (value < itemInfo->ItemCount) {
					targetSlot->GetItemData()->ItemCount += value;
					itemInfo->ItemCount -= value;
				}
				else {
					targetSlot->GetItemData()->ItemCount += itemInfo->ItemCount;
					PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(ContainerPanel->ContainerCategory), itemInfo->SlotIndex, true);
					break;
				}
			}
			else {
				FVector2D findLocation = otherContainer->FindEmptySlot(itemSize);
				if (findLocation != FVector2D(-1.0f)) {
					PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(ContainerPanel->ContainerCategory), itemInfo->SlotIndex, false);
					itemInfo->SlotIndex = findLocation;
					PlayerController->PlayerData->AddItemTo(PlayerController->PlayerData->GetTargetContainer(otherCategory), itemInfo);
				}
				break;
			}
		}

		ContainerPanel->ShowContainer(PlayerController->PlayerData->GetTargetContainer(ContainerPanel->ContainerCategory));
		otherContainer->ShowContainer(PlayerController->PlayerData->GetTargetContainer(otherCategory));

		if (ContainerPanel->ContainerCategory == EContainerCategory::Trade) {
			PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
		}

		if (otherCategory == EContainerCategory::Trade && ContainerPanel->ContainerCategory == EContainerCategory::Storage) {
			PlayerController->InventoryUI->Widget_Trade->bIsSell = true;;
			PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
		}
	}
}