// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Container_Base.h"
#include "CraftInventory.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UCraftInventory : public UContainer_Base
{
	GENERATED_BODY()
	
public:
	void CraftInventoryInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size);
};
