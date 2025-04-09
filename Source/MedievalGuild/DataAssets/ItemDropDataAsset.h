// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDropDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemDropDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UItemDropDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TMap<int, int> DropItemInfo;
};
