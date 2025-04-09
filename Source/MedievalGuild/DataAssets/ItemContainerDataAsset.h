// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemContainerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemContainerDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UItemContainerDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TMap<int, int> ItemInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TMap<int, int> ItemMinCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TMap<int, int> ItemMaxCount;
};
