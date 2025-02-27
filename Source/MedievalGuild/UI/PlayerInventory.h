// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemUI_Base.h"
#include "ItemSlot.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

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

#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerInventory(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;

protected:
	void MakeInventory(int col, int row);
	void MakeItemToSlot(int col, int row, int sizeX, int sizeY, int count);
	void MoveItemToSlot(int fromCol, int fromRow, int toCol, int toRow);
	void SlotInitSetting(UButton* button);

	UWidget* GetInventorySlot(int col, int row);

	float InventorySlotSize = 100.0f;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventorySlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotGridPanel;
};
