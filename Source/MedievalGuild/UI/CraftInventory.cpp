// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftInventory.h"

void UCraftInventory::CraftInventoryInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size)
{
	ContainerInitSetting(InitWidgetClass[0], InitWidgetClass[1], InitWidgetClass[2], InitWidgetClass[3], category, size);
}
