// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemScaleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemScaleDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UItemScaleDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	float Scale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	FRotator Rotation;
};
