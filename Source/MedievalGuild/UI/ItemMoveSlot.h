// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridPanel.h"

#include "ItemMoveSlot.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemMoveSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitSetting(FVector2D slotSize);

public:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* MovingSlot;
};
