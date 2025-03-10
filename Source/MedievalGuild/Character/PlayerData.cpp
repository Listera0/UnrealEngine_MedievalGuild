// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

void APlayerData::AddItemToInventory(int slot, UItemData* item, int count)
{
    // 해당 슬롯에 아이템이 이미 있는지 확인
    FInventoryData* existingItem = FindSlotItem(slot);

    if (existingItem) // 이미 있으면 수량만 추가
    {
        existingItem->ItemCount += count;
    }
    else // 없으면 새로 아이템 추가
    {
        FInventoryData newItem(slot, item, count); // FInventoryData 객체 생성
        PlayerInventory.Add(newItem);  // TArray에 추가
    }
}

void APlayerData::RemoveItemFromInventory(int slot, UItemData* item, int count)
{
}

FInventoryData* APlayerData::FindSlotItem(int slot)
{
    for (FInventoryData& data : PlayerInventory)
    {
        if (data.SlotIndex == slot)
        {
            return &data;  // 해당 슬롯 아이템 반환
        }
    }
    return nullptr;  // 없으면 nullptr 반환
}


// PlayerData (PlayerState)에 아이템 인벤토리에 관한 데이터가 있고
// PlayerInventoryUI (UserWidget)에 아이템 인벤토리에 관련된 UI가 있음
// 아이템 생성 제거의 시작 위치
// 아이템을 이동시키면 그 함수의 시작 위치