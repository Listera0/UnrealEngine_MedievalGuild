// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "../Item/ItemData.h"
#include "../UI/PlayerInventory.h"
#include "../Object/InventoryData.h"

#include "PlayerData.generated.h"


UCLASS()
class MEDIEVALGUILD_API APlayerData : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddItemToInventory(FVector2D slot, UItemData* item, int count);

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void RemoveItemFromInventory(int slot, UItemData* item, int count);

	void MoveItemIndex(FVector2D from, FVector2D to);

protected:
	FInventoryData* FindSlotItem(FVector2D slot);
	FVector2D FindItemSlot(UItemData* item);
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
