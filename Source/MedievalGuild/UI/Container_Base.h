// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateBrush.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#include "ItemSlotImg.h"
#include "ItemUI_Base.h"
#include "ItemSlot.h"
#include "ContainerEnum.h"
#include "../Item/ItemData.h"
#include "../Object/InventoryData.h"
#include "../Object/ContainerCategory.h"

#include "Container_Base.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UContainer_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	UContainer_Base(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotImgClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;

public:
	void ContainerInitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
								TSubclassOf<UUserWidget> itemSlotImgClass, EContainerCategory category, FVector2D size);
	void MakeContainer(FVector2D size);
	void ResetContainer();
	virtual void ShowContainer(TArray<FInventoryData*>& data);
	virtual void ShowContainer(FInventoryData* data);

	void MakeItemUI(FInventoryData* data);
	FVector2D MakeItem(FInventoryData* data);

	void MoveItemToSlot(EContainerCategory before, int fromIndex, int toIndex, TArray<UItemUI_Base*> items);
	void MoveItemToSlot(EContainerCategory before, int fromIndex, int toIndex, TArray<UItemUI_Base*> items, bool equipment); // for move equipment from equiopment slot
	void MoveItemToSlot(EContainerCategory before, FInventoryData* itemData); // for move equipment to equipment slot

	/// <summary>
	/// If checkMax is ture -> check item count less then item maxStack
	/// </summary>
	UItemSlot* HasItem(UItemData* item, bool checkMax);
	FVector2D FindEmptySlot(FVector2D size);
	FInventoryData* FindContainerSlotData(TArray<FInventoryData*>& data, FVector2D slotIndex);
	void SlotInitSetting(UButton* button);
	void SlotInitSetting(UImage* image);
	UItemSlot* GetContainerSlot(FVector2D index);

protected:
	int GetEquipmentIndex(EItemType type);
	inline bool IsInContainer(FVector2D index) { return (index.X < ContainerSize.X && index.Y < ContainerSize.Y && index.X >= 0 && index.Y >= 0); };

	float ContainerSlotSize = 100.0f;


public:
	EContainerCategory ContainerCategory;
	FVector2D ContainerSize;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ContainerSlot;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ContainerSlotGrid;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ContainerSlotImgGrid;

	TArray<UItemSlot*> ContainerItemSlots;
};