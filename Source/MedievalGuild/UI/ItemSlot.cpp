// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "Container_Base.h"
#include "../Framework/PlayerCharacterController.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/GameUserSettings.h"

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
				if (PlayerController->InventoryUI->Widget_Trade->bIsSell) { return Reply.NativeReply; }
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
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Storage) {
				if (PlayerController->InteractObj && PlayerController->InteractObj->ActorHasTag("Merchant")) {
					if (PlayerController->InventoryUI->Widget_Trade->bIsBuy) {
						Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
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
			else {
				if (PlayerController->IsShiftPressed()) { SlotButtonShiftClick(); }
				else { Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton); }
			}
		}
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) {
		if (HasItem()) {
			ShowInteractItemPanel();
		}
	}

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

		TArray<UItemUI_Base*> draggingItems;

		// 가져온 모든 아이템들 복제본 만들어 슬롯에 넣기
		for (int i = 0; i < movingItems.Num(); i++) {
			UItemUI_Base* draggingItem = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			draggingItem->SetItemData(movingItems[i]->ItemData);
			draggingItem->SetItemIndex(movingItems[i]->ItemIndex);
			draggingItem->SetItemImage(draggingItem->ItemData->ItemData, draggingItem->ItemIndex);
			if (draggingItem->ItemIndex == FVector2D(draggingItem->ItemData->ItemData->width - 1, draggingItem->ItemData->ItemData->height - 1)) draggingItem->SetItemCountText();

			draggingItems.Add(draggingItem);
			movingItems[i]->SetVisibility(ESlateVisibility::Collapsed);

			UUniformGridSlot* gridSlot = dragSlot->MovingSlot->AddChildToUniformGrid(draggingItem, draggingItem->ItemIndex.Y, draggingItem->ItemIndex.X);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}


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
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Trade && PlayerController->InventoryUI->Widget_Trade->bIsBuy) { return false; }
			else if (before == EContainerCategory::Trade) {
				UTradeWidget* tradeWidget = PlayerController->InventoryUI->Widget_Trade;
				if (tradeWidget->bIsBuy) { return false; }
				if (tradeWidget->bIsSell) { 
					ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
				}
			}
			else if (PlayerController->PlayerData->GetEquipmentIndex(ContainerPanel->ContainerCategory) != -1) { // is equipment
				if (HasItem()) { return false; }
				int containerTypeIndex = GetEquipmentIndex(ownerItem->ItemData->ItemData->eItemType);
				if (containerTypeIndex == -1) return false;
				if (containerTypeIndex != PlayerController->PlayerData->GetEquipmentIndex(ContainerPanel->ContainerCategory)) { return false; }

				ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, ownerItem->ItemData);
			}
			else {
				ContainerPanel->MoveItemToSlot(Operation->PrevContainerCategory, Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
			}

			if (ContainerPanel->ContainerCategory == EContainerCategory::Trade && before == EContainerCategory::Storage) {
				PlayerController->InventoryUI->Widget_Trade->bIsSell = true;
				PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
			}
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Storage && before == EContainerCategory::Trade) {
				PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
			}
			else if (GetEquipmentIndex(ContainerPanel->ContainerCategory) != -1 || GetEquipmentIndex(before) != -1) {
				PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
			}
			else if (ContainerPanel->ContainerCategory == EContainerCategory::Inventory || before == EContainerCategory::Inventory) {
				PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
			}

			if (PlayerController->InteractObj && PlayerController->InteractObj->ActorHasTag("Merchant") && 
				ContainerPanel->ContainerCategory == EContainerCategory::Storage) {
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

int UItemSlot::GetEquipmentIndex(EContainerCategory containerCategory)
{
	int returnValue = -1;

	switch (containerCategory) {
	case EContainerCategory::Helmet: returnValue = 0; break;
	case EContainerCategory::Cloth: returnValue = 1; break;
	case EContainerCategory::Shoes: returnValue = 2; break;
	case EContainerCategory::Bag: returnValue = 3; break;
	case EContainerCategory::Weapon: returnValue = 4; break;
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
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
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

		if (otherCategory == EContainerCategory::Trade && ContainerPanel->ContainerCategory == EContainerCategory::Storage) {
			PlayerController->InventoryUI->Widget_Trade->bIsSell = true;
			PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
		}
		else if (otherCategory == EContainerCategory::Storage && ContainerPanel->ContainerCategory == EContainerCategory::Trade) {
			PlayerController->InventoryUI->Widget_Trade->ShowTotalPrice();
		}
		else if (GetEquipmentIndex(ContainerPanel->ContainerCategory) != -1 || GetEquipmentIndex(otherCategory) != -1) {
			PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
		}
		else if (ContainerPanel->ContainerCategory == EContainerCategory::Inventory || otherCategory == EContainerCategory::Inventory) {
			PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
		}
	}
}

FVector2D UItemSlot::ShowInteractItemPanel()
{
	// Get Optional Value
	FVector2D WindowPosition = FSlateApplication::Get().GetActiveTopLevelWindow()->GetPositionInScreen();
	FVector2D ContainerPanelPosition = ContainerPanel->ContainerSlotGrid->GetCachedGeometry().GetAbsolutePosition();
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	FVector2D ScreenResolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
	FVector2D TargetSlotColRow = SlotColRow - FVector2D(GetSlotItem()->ItemIndex.X, 0.0f) + FVector2D((float)(GetItemData()->ItemData->width - 1), 0.0f);

	FVector2D Scale = ViewportSize / ScreenResolution;

	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("%f, %f"), Scale.X, Scale.Y));

	// Set SlotPosition to ViewportPostion
	FVector2D SlotPosition = (TargetSlotColRow + FVector2D(0.5f, 0.5f)) * SlotSize;
	FVector2D PositionOffset = FVector2D(30.0f, -30.0f);

	// Get ScreenPosition between window and container
	FVector2D ScreenPosition = ContainerPanelPosition - WindowPosition + SlotPosition + PositionOffset;

	// Trans to Viewport from Screen
	FVector2D ViewportPosition = ScreenPosition * Scale;

	FVector2D FinalViewportPosition = ViewportPosition;
	PlayerController->ItemInteractUI->SetPositionInViewport(FinalViewportPosition);
	PlayerController->ItemInteractUI->InteractItem = GetItemData();
	PlayerController->ItemInteractUI->ShowPanelSetting(Scale);
	PlayerController->RecordMousePosition();

	return FVector2D();
}
