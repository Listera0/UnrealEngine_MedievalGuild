// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMoveSlot.h"

void UItemMoveSlot::InitSetting(FVector2D slotSize)
{
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(MovingSlot->Slot);

	slot->SetSize(slotSize);
}
