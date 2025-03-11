// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemMoveManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemMoveManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Item Move Manager")
	static UItemMoveManager* GetInstance();

private:
	static UItemMoveManager* Instance;
};
