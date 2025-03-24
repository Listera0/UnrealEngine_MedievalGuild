// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Container_Base.h"

#include "PlayerStorage.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerStorage : public UContainer_Base
{
	GENERATED_BODY()
	
public:
	void ShowContainer(TArray<FInventoryData*>& data) override;
	int GetTotalGold();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnGold;
};
