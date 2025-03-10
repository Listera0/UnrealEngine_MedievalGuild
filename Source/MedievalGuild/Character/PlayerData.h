// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "../Item/ItemData.h"
#include "../UI/PlayerInventory.h"

#include "PlayerData.generated.h"

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SlotIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItemData* ItemData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ItemCount;

	FInventoryData() : SlotIndex(0), ItemData(nullptr), ItemCount(0) {};
	FInventoryData(int slotIndex, UItemData* itemData, int itemCount) : SlotIndex(slotIndex), ItemData(itemData), ItemCount(itemCount) {};
};

UCLASS()
class MEDIEVALGUILD_API APlayerData : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddItemToInventory(int slot, UItemData* item, int count);

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void RemoveItemFromInventory(int slot, UItemData* item, int count);

protected:
	FInventoryData* FindSlotItem(int slot);
	void MakePlayerInventoryUI();
	void ChangePlayerInventoryUI();
	void ShowPlayerInventory();
	
public:
	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerStemina;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerEnergy;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	TArray<FInventoryData> PlayerInventory;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	TArray<FInventoryData> PlayerContainer;

	UPROPERTY()
	UPlayerInventory* PlayerInventoryUI;

private:
	FInventoryData* FindData;
public:
	// 나중에 서버에서 사용시 DOREPLIFETIME(APlayerData, PlayerName); 로 자동 동기화 작업을 해줘야함
	// 동기화 하고자 하는 값들의 UPROPERTY에 'Replicated'를 포함시키기
	// virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
