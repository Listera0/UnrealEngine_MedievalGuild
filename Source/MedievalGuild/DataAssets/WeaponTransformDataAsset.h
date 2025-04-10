// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponTransformDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UWeaponTransformDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UWeaponTransformDataAsset();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int index;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FTransform transfrom;
};
