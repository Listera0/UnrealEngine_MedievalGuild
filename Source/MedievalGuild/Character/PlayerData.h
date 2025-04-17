// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "../Item/ItemData.h"
#include "../UI/PlayerInventory.h"
#include "../Object/InventoryData.h"
#include "../Quest/QuestComponent.h"

#include "PlayerData.generated.h"


UCLASS()
class MEDIEVALGUILD_API APlayerData : public APlayerState
{
	GENERATED_BODY()

public:
	APlayerData(const FObjectInitializer& ObjectInitializer);

	bool CheckHasItem(int index, int count);
	void AddItemToAllWork(TArray<FInventoryData*>& target, FInventoryData* item, UContainer_Base* targetContainer);
	void AddItemTo(TArray<FInventoryData*>& target, FInventoryData* item);
	void RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, int count, bool withDelete);
	void RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, bool withDelete);
	int RemoveItemTo(TArray<FInventoryData*>& target, UItemData* item, int count, bool withDelete);
	void MoveItemIndex(TArray<FInventoryData*>& target, FVector2D from, FVector2D to); // 내부용
	void MoveItemIndex(TArray<FInventoryData*>& target, FVector2D to, FInventoryData* data); // 외부용
	void EmptyInventory();

	FInventoryData* HasItem(TArray<FInventoryData*>& target, int itemIndex, bool checkMaxStack);
	FInventoryData* FindItemWithLocation(TArray<FInventoryData*>& target, FVector2D location);
	FVector2D FindEmptySlot(TArray<FInventoryData*>& target, UContainer_Base* targetPanel, FInventoryData* targetItem);
	bool ContainsTArray(TArray<FVector2D> slot, FVector2D target);

	TArray<FInventoryData*>& GetTargetContainer(EContainerCategory category);
	int GetEquipmentIndex(EContainerCategory category);
	int GetEquipmentIndex(EItemType category);
	int GetPlayerCurrency();
	int GetItemCount(int index);

	void SaveGame();
	void LoadGame();

public:
	class APlayerCharacterController* PlayerController = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	FName PlayerName;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	float PlayerHealth;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	float PlayerStemina;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerState")
	float PlayerEnergy;

	TArray<FInventoryData*> PlayerInventory;
	TArray<FInventoryData*> PlayerStorage;
	TArray<FInventoryData*> PlayerEquipment;
	TArray<FInventoryData*> PlayerTrade;

	UPROPERTY()
	UPlayerInventory* PlayerInventoryUI;
	
public:
	// 나중에 서버에서 사용시 DOREPLIFETIME(APlayerData, PlayerName); 로 자동 동기화 작업을 해줘야함
	// 동기화 하고자 하는 값들의 UPROPERTY에 'Replicated'를 포함시키기
	// virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	UQuestComponent* QuestCompo = nullptr;
};
