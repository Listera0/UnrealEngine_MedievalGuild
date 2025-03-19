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

	void AddItemToAllWork(TArray<FInventoryData*>& target, FInventoryData* item, UContainer_Base* targetContainer);
	void AddItemTo(TArray<FInventoryData*>& target, FInventoryData* item);
	void RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, int count, bool withDelete);
	void RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, bool withDelete);
	void RemoveItemTo(TArray<FInventoryData*>& target, UItemData* item, int count, bool withDelete);
	void MoveItemIndex(TArray<FInventoryData*>& target, FVector2D from, FVector2D to); // 내부용
	void MoveItemIndex(TArray<FInventoryData*>& target, FVector2D to, FInventoryData* data); // 외부용

	FInventoryData* HasItem(TArray<FInventoryData*>& target, int itemIndex, bool checkMaxStack);
	FInventoryData* FindItemWithLocation(TArray<FInventoryData*>& target, FVector2D location);

	TArray<FInventoryData*>& GetTargetContainer(EContainerCategory category);
	int GetEquipmentIndex(EContainerCategory category);
	int GetPlayerCurrency();

public:
	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerStemina;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	float PlayerEnergy;

	TArray<FInventoryData*> PlayerInventory;
	TArray<FInventoryData*> PlayerStorage;
	TArray<FInventoryData*> PlayerTrade;
	TArray<FInventoryData*> PlayerEquipment;

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
