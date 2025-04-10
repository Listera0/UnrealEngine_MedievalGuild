// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemEffectDataAsset.generated.h"


UENUM(BlueprintType)
enum class EEffectTarget : uint8
{
	Health = 0,

	None
};

UCLASS()
class MEDIEVALGUILD_API UItemEffectDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UItemEffectDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	int ItemIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TArray<EEffectTarget> ItemTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Option")
	TArray<float> TargetValue;
};
