// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Character/PlayerData.h"
#include "../Object/InventoryData.h"
#include "InteractObject_Base.h"
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

public:
	//void MoveItem(EMoveParam move, FInventoryData* item, FVector2D location);
	//void SetPlayerData(APlayerData* data) { PlayerData = data; }
	//void SetInteractObj(AInteractObject_Base* obj) { InteractObj = obj; }

protected:
	APlayerData* PlayerData;
	AInteractObject_Base* InteractObj;
};
