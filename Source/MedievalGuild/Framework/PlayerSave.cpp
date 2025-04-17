// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSave.h"
#include "../Item/ItemDataManager.h"

void UPlayerSave::RecordSaveBaseData(int saveIndex, FName playerName, float health, float stemina, float energy)
{
	SaveIndex = saveIndex;
	PlayerName = playerName;
	PlayerHealth = health;
	PlayerStemina = stemina;
	PlayerEnergy = energy;
}

void UPlayerSave::RecordSaveItemData(TArray<FInventoryData*> inv, TArray<FInventoryData*> storage, TArray<FInventoryData*> equip)
{
	InventoryData.Empty();
	StorageData.Empty();
	EquipmentData.Empty();
	EquipmentData.Init(FSaveItemData(), 5);

	for (FInventoryData* data : inv) {
		InventoryData.Add(FSaveItemData(data->SlotIndex, data->ItemData->index, data->ItemCount));
	}

	for (FInventoryData* data : storage) {
		StorageData.Add(FSaveItemData(data->SlotIndex, data->ItemData->index, data->ItemCount));
	}

	for (int i = 0; i < equip.Num(); i++) {
		if (equip[i]) {
			EquipmentData[i] = FSaveItemData(equip[i]->SlotIndex, equip[i]->ItemData->index, equip[i]->ItemCount);
		}
	}
}

void UPlayerSave::ExtractSaveBaseData(FName& playerName, float& health, float& stemina, float& energy)
{
	playerName = PlayerName;
	health = PlayerHealth;
	stemina = PlayerStemina;
	energy = PlayerEnergy;
}

void UPlayerSave::ExtractSaveItemData(TArray<FInventoryData*>& inv, TArray<FInventoryData*>& storage, TArray<FInventoryData*>& equip)
{
	UItemDataManager* DataManager = UItemDataManager::GetInstance();

	inv.Empty();
	storage.Empty();
	equip.Empty();
	equip.Init(nullptr, 5);

	for (FSaveItemData data : InventoryData) {
		inv.Add(new FInventoryData(data.SlotIndex, DataManager->FindItemData(data.ItemIndex), data.ItemCount));
	}

	for (FSaveItemData data : StorageData) {
		storage.Add(new FInventoryData(data.SlotIndex, DataManager->FindItemData(data.ItemIndex), data.ItemCount));
	}

	for (int i = 0; i < EquipmentData.Num(); i++) {
		if (EquipmentData[i].ItemIndex != 0) {
			equip[i] = new FInventoryData(EquipmentData[i].SlotIndex, DataManager->FindItemData(EquipmentData[i].ItemIndex), EquipmentData[i].ItemCount);
		}
	}
}
