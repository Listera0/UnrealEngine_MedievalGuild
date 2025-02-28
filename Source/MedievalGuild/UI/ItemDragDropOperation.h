// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"

#include "ItemUI_Base.h"

#include "ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	void SetOrigianlWidgets(TArray<UItemUI_Base*> widgets) {
		OriginalWidgets.Empty();
		OriginalWidgets.Append(widgets);
	}

public:
	UPROPERTY()
	TArray<UItemUI_Base*> OriginalWidgets;

	int PrevSlotIndex;

	bool bMoveSuccessed;
};
