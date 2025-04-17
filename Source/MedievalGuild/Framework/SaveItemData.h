// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveItemData.generated.h"

USTRUCT(BlueprintType)
struct FSaveItemData
{
	GENERATED_BODY()

	FSaveItemData() { SlotIndex = FVector2D(-1.0f), ItemIndex = 0; ItemCount = 1; };
	FSaveItemData(FVector2D slotIndex, int index, int count) { SlotIndex = slotIndex; ItemIndex = index; ItemCount = count; };

public:
	UPROPERTY(BlueprintReadWrite)
	FVector2D SlotIndex;
	UPROPERTY(BlueprintReadWrite)
	int ItemIndex;
	UPROPERTY(BlueprintReadWrite)
	int ItemCount;
};