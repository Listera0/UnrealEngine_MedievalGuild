// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "Container_Base.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(false);
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
		FVector2D itemIndex = movingItems[0]->ItemIndex;
		FVector2D itemSize = movingItems[0]->ItemSize;
		dragSlot->InitSetting(SlotSize * movingItems[0]->ItemSize);

		// 가져온 모든 아이템들 복제본 만들어 슬롯에 넣기
		for (int i = 0; i < movingItems.Num(); i++) {
			UItemUI_Base* draggingItem = CreateWidget<UItemUI_Base>(GetWorld(), ItemBaseClass);
			movingItems[i]->SetDuplicateInit(draggingItem);
			movingItems[i]->SetVisibility(ESlateVisibility::Collapsed);

			UUniformGridSlot* gridSlot = dragSlot->MovingSlot->AddChildToUniformGrid(draggingItem, draggingItem->ItemIndex.X, draggingItem->ItemIndex.Y);
			gridSlot->SetHorizontalAlignment(HAlign_Fill);
			gridSlot->SetVerticalAlignment(VAlign_Fill);
		}
		//dragSlot->MovingSlot->SetRenderTransform(FWidgetTransform((-itemIndex * SlotSize), FVector2D(1.0f), FVector2D(), 0.0f));

		FVector2D CustomOffset = FVector2D(GetOffSetValue(itemIndex.X, itemSize.X), GetOffSetValue(itemIndex.Y, itemSize.Y));
		FVector2D CustomOffset2 = ((itemSize - itemIndex) * -SlotSize * 0.5f);
		FVector2D CustomOffset3 = (itemIndex - ((itemSize - 1) * 0.5f)) * -SlotSize;

		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(dragSlot->MovingSlot->Slot);
		//canvasSlot->SetPosition(itemIndex * -SlotSize);
		canvasSlot->SetPosition(CustomOffset3);

		Operation->PrevContainerGroup = ContainerPanel->ContainerGroup;
		Operation->PrevSlotOwner = GetOuter();
		Operation->PrevSlotIndex = SlotIndex;
		Operation->bMoveSuccessed = false;
		Operation->SetOrigianlWidgets(movingItems);
		Operation->DefaultDragVisual = dragSlot;
		//Operation->Offset = CustomOffset;

		// 원인 : 생성되고 크기 조절할 때 처음 위치가 고정되어서 그런것
		// 제한사항 1 : DragDropOperation을 사용할시 강제로 offset이 적용됨(offset 제어 불가) 중앙으로 이동됨
		// 제한사항 2 : 위젯 자체의 위치를 옮기고 싶어도 크기를 조정하면 anchor가 이동됨
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
		if (Operation->OriginalWidgets[0] != GetSlotItem()) {
			Operation->bMoveSuccessed = true;
			ContainerPanel->MoveItemToSlot(Operation->PrevContainerGroup, Operation->PrevSlotIndex, SlotIndex, Operation->OriginalWidgets);
		}
	}

	return false;
}


