// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveItemData.h"
#include "../Object/InventoryData.h"
#include "PlayerSave.generated.h"

UCLASS()
class MEDIEVALGUILD_API UPlayerSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	void RecordSaveBaseData(int saveIndex, FName playerName, float health, float stemina, float energy);
	void RecordSaveItemData(TArray<FInventoryData*> inv, TArray<FInventoryData*> storage, TArray<FInventoryData*> equip);

	void ExtractSaveBaseData(FName& playerName, float& health, float& stemina, float& energy);
	void ExtractSaveItemData(TArray<FInventoryData*>& inv, TArray<FInventoryData*>& storage, TArray<FInventoryData*>& equip);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int SaveIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FName PlayerName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float PlayerHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float PlayerStemina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float PlayerEnergy;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FSaveItemData> InventoryData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FSaveItemData> StorageData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FSaveItemData> EquipmentData;	
};
