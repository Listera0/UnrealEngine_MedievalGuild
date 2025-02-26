// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"

#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerInventory : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	void MakeInventory(int col, int row);
	void MakeItemToSlot(int col, int row);
	void SlotInitSetting(UButton* button);

	float InventorySlotSize = 100.0f;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* InventorySlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotGridPanel;
};
