// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemDragDropOperation.h"
#include "ItemMoveSlot.h"
#include "ItemUI_Base.h"
#include "../Object/InventoryData.h"

#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;

	inline bool HasItem() { return ItemSlot->GetChildrenCount() > 0 ? true : false; }
	inline UItemUI_Base* GetSlotItem() { return Cast<UItemUI_Base>(ItemSlot->GetChildAt(0)); }
	inline FInventoryData* GetItemData() { return HasItem() ? GetSlotItem()->GetOwnerItem()->ItemData : nullptr; }
	int GetEquipmentIndex(EItemType itemType);
	int GetEquipmentIndex(EContainerCategory containerCategory);
	void RemoveItem();
	void SlotButtonShiftClick();
	
protected:
	inline float GetOffSetValue(int index, int size) { return -((index - ((size - 1) * 0.5f)) * 2.0f * (0.5f / size)); };
	FVector2D ShowInteractItemPanel();

public:
	class APlayerCharacterController* PlayerController;
	class UContainer_Base* ContainerPanel;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemSlot;

	FVector2D SlotColRow;
	int SlotIndex;
	float SlotSize;
};
