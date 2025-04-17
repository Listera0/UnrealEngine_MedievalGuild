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
	virtual void ShowContainer(TArray<FInventoryData*>& data) override;
	
	void CraftInventoryInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size);
	void GetCraftItemList();

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CraftTableName = nullptr;
};
