// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "PlayerInventory.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply UItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("Mouse Button Down Left"));

		if (ItemSlot->GetChildrenCount() != 0) {
			Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
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
		int itemIndexX = movingItems[0]->ItemIndexX; int itemIndexY = movingItems[0]->ItemIndexY;
		int itemSizeX = movingItems[0]->ItemSizeX; int itemSizeY = movingItems[0]->ItemSizeY;
		dragSlot->InitSetting(SlotSize * movingItems[0]->ItemSizeX, SlotSize * movingItems[0]->ItemSizeY);

		// 가져온 모든 아이템들 복제본 만들어 슬롯에 넣기
		for (int i = 0; i < movingItems.Num(); i++) {
			UItemUI_Base* draggingItem = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			movingItems[i]->SetDuplicateInit(draggingItem);
			movingItems[i]->SetRenderOpacity(0.0f);

			UUniformGridSlot* gridSlot = dragSlot->MovingSlot->AddChildToUniformGrid(draggingItem, draggingItem->ItemIndexX, draggingItem->ItemIndexY);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}

		Operation->PrevSlotIndex = SlotIndex;
		Operation->bMoveSuccessed = false;
		Operation->SetOrigianlWidgets(movingItems);
		Operation->DefaultDragVisual = dragSlot;
		FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		FVector2D CustomOffset = FVector2D(GetOffSetValue(itemIndexX,itemSizeX), GetOffSetValue(itemIndexY, itemSizeY));

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%f, %f"), CustomOffset.X, CustomOffset.Y));
		Operation->Offset = CustomOffset;

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("Mouse Dragged"));
	}
}

void UItemSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UItemDragDropOperation* Operation = Cast<UItemDragDropOperation>(InOperation);

	if (Operation) {
		for (int i = 0; i < Operation->OriginalWidgets.Num(); i++) {
			Operation->OriginalWidgets[i]->SetRenderOpacity(1.0f);
		}

		if (!Operation->bMoveSuccessed) {
			// turn back
		}
	}
}

bool UItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UItemDragDropOperation* Operation = Cast<UItemDragDropOperation>(InOperation);

	if (Operation) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("Get Item"));
		if (Operation->PrevSlotIndex != SlotIndex) {
			Operation->bMoveSuccessed = true;
			InventoryPanel->MoveItemToSlot(Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
		}
	}

	return false;
}


