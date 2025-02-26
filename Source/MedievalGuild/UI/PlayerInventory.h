// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/GridSlot.h"

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

	float InventorySlotSize = 5.0f;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotGridPanel;
};
