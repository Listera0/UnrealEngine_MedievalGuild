// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemRecipe.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemRecipe : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Recipe")
	int MakeItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Recipe")
	int MakeItemAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Recipe")
	TArray<int> IngredientsIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Recipe")
	TArray<int> IngredientsAmount;

};
