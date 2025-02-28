// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMoveSlot.h"

void UItemMoveSlot::InitSetting(float slotSizeX, float slotSizeY)
{
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(MovingSlot->Slot);

	slot->SetSize(FVector2D(slotSizeX, slotSizeY));
}
