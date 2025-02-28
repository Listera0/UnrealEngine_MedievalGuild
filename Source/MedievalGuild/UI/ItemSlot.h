// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemDragDropOperation.h"
#include "ItemMoveSlot.h"
#include "ItemUI_Base.h"

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
	
protected:
	float GetOffSetValue(int index, int size) { return -((index - ((size - 1) * 0.5f)) * 2.0f * (0.5f / size)); };

public:
	class UPlayerInventory* InventoryPanel;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemSlot;

	float SlotSize;
	int SlotIndex;

	FVector2D SlotColRow;
};
