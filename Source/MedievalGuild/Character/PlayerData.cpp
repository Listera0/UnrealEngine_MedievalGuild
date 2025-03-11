// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

void APlayerData::AddItemToInventory(FVector2D slot, UItemData* item, int count)
{
    // 슬롯을 지정하지 않았을 때
    if (slot == FVector2D(-1.0f)) {
        // 같은 아이템이 존재하지 않을 때
        FVector2D itemSlotIndex = FindItemSlot(item);
        if (itemSlotIndex == FVector2D(-1.0f)) {
            FVector2D findSlot = PlayerInventoryUI->Widget_Inventory->FindEmptySlot(item->width, item->height);
            if (findSlot != FVector2D(-1.0f)) {
                // 최대 스택보다 클 때
                if (count > item->maxStack) {
                    FInventoryData newItem(findSlot, item, item->maxStack);
                    PlayerInventory.Add(newItem);
                    PlayerInventoryUI->Widget_Inventory->MakeItemToSlot(findSlot, item, item->maxStack);
                    AddItemToInventory(FVector2D(-1.0f), item, count - item->maxStack);
                }
                else {
                    FInventoryData newItem(findSlot, item, count);
                    PlayerInventory.Add(newItem);
                    PlayerInventoryUI->Widget_Inventory->MakeItemToSlot(findSlot, item, count);
                }
            }
        }
        else {
            FInventoryData* findItem = FindSlotItem(itemSlotIndex);
            int beforeCount = findItem->ItemCount;
            int maxCount = findItem->ItemData->maxStack;
            if (beforeCount + count > maxCount) {
                findItem->ItemCount = maxCount;
                PlayerInventoryUI->Widget_Inventory->SetItemInfo(findItem->SlotIndex, findItem->ItemCount);
                AddItemToInventory(FVector2D(-1.0f), item, (count - (maxCount - beforeCount)));
            }
            else {
                findItem->ItemCount += count;
                PlayerInventoryUI->Widget_Inventory->SetItemInfo(findItem->SlotIndex, findItem->ItemCount);
            }
        }
    }
    else {
        FInventoryData* findItem = FindSlotItem(slot);
        if (findItem) {
            findItem->ItemCount += count;
            PlayerInventoryUI->Widget_Inventory->SetItemInfo(findItem->SlotIndex, findItem->ItemCount);
        }
        else {
            FInventoryData newItem(slot, item, count);
            PlayerInventory.Add(newItem);
            PlayerInventoryUI->Widget_Inventory->MakeItemToSlot(slot, item, count);
        }
    }
}

void APlayerData::RemoveItemFromInventory(int slot, UItemData* item, int count)
{
}

FInventoryData* APlayerData::FindSlotItem(FVector2D slot)
{
    for (FInventoryData& data : PlayerInventory)
    {
        if (data.SlotIndex == slot)
        {
            return &data;  // 해당 슬롯 아이템 반환
        }
    }
    return nullptr;
}

FVector2D APlayerData::FindItemSlot(UItemData* item) {
    for (FInventoryData& data : PlayerInventory)
    {
        if (data.ItemData->index == item->index && data.ItemCount < item->maxStack)
        {
            return data.SlotIndex;
        }
    }
    return FVector2D(-1.0f);
}

void APlayerData::MoveItemIndex(FVector2D from, FVector2D to)
{
    FindSlotItem(from)->SlotIndex = to;
}
