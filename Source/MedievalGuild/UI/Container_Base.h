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
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;

public:
	void ContainerInitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
								EContainerCategory category, float col, float row);
	void MakeContainer(int col, int row);
	void ResetContainer();
	void ShowContainer(TArray<FInventoryData*> data);

	void MakeItemToSlot(int col, int row, int sizeX, int sizeY, int count);
	void MakeItemToSlot(int sizeX, int sizeY, int count);
	void MakeItemToSlot(FVector2D index, UItemData* item, int count);
	FVector2D MakeItemToSlot(UItemData* item, int count);

	void MoveItemToSlot(EContainerCategory before, int fromIndex, int toIndex, TArray<UItemUI_Base*> items);
	void SetItemInfo(FVector2D index, int count);

	FVector2D FindEmptySlot(int sizeX, int sizeY);
	void SlotInitSetting(UButton* button);

protected:
	UItemSlot* GetContainerSlot(int col, int row);
	UItemSlot* GetContainerSlot(FVector2D index);

	inline bool IsInContainer(FVector2D index) { return (index.X < ContainerSize.X && index.Y < ContainerSize.Y && index.X >= 0 && index.Y >= 0); };

	float ContainerSlotSize = 100.0f;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ContainerSlot;
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ContainerSlotGrid;

	TArray<UItemSlot*> ContainerItemSlots;
	FVector2D ContainerSize;

public:
	EContainerCategory ContainerCategory;
};