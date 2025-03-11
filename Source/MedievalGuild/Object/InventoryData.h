// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemDataManager.h"
#include "InventoryData.generated.h"


USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D SlotIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItemData* ItemData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ItemCount;

	FInventoryData() : SlotIndex(0), ItemData(nullptr), ItemCount(0) {};
	FInventoryData(FVector2D slotIndex, UItemData* itemData, int itemCount) : SlotIndex(slotIndex), ItemData(itemData), ItemCount(itemCount) {};
};
