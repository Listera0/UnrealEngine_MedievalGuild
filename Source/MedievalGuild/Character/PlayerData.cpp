// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "../Framework/PlayerCharacterController.h"

void APlayerData::AddItemTo(TArray<FInventoryData*>& target, FInventoryData* data)
{
    FInventoryData* targetData = HasItem(target, data->ItemData->index, true);
    if (!targetData) { target.Add(data); }

    /*if (data->SlotIndex == FVector2D(-1.0f)) {
        FInventoryData* targetData = HasItem(target, data->ItemData->index, true);
        if (targetData) {
            int value = targetData->ItemData->maxStack - targetData->ItemCount;
            if (value < data->ItemCount) {
                targetData->ItemCount = targetData->ItemData->maxStack;
                data->ItemCount -= value;
                AddItemTo(target, data);
            }
            else {
                targetData->ItemCount += data->ItemCount;
            }
        }
        else {
            target.Add(data);
        }
    }
    else {
        FInventoryData* targetData = FindItemWithLocation(target, data->SlotIndex);
        if (targetData) {
            if (targetData->ItemData->index == data->ItemData->index) {
                int value = targetData->ItemData->maxStack - targetData->ItemCount;
                if (value < data->ItemCount) {
                    targetData->ItemCount = targetData->ItemData->maxStack;
                    data->ItemCount -= value;
                    data->SlotIndex = FVector2D(-1.0f);
                    AddItemTo(target, data);
                }
                else {
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("before %s {%d}"), *targetData->ItemData->name, targetData->ItemCount));
                    targetData->ItemCount += data->ItemCount;
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Add %s +%d = {%d}"), *targetData->ItemData->name, data->ItemCount, targetData->ItemCount));
                }
            }
        }
        else {
            target.Add(data);
        }
    }*/
}

void APlayerData::RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, int count, bool withDelete)
{
    FInventoryData* targetData = FindItemWithLocation(target, location);
    if (targetData) {
        if (targetData->ItemCount < count) {
            target.Remove(targetData);
            if(withDelete) delete targetData;
        }
        else {
            targetData->ItemCount -= count;
        }
    }
}

void APlayerData::RemoveItemTo(TArray<FInventoryData*>& target, FVector2D location, bool withDelete)
{
    for (int i = 0; i < target.Num(); i++) {
        if (target[i]->SlotIndex == location) {
            target.RemoveAt(i);
        }
    }
}

void APlayerData::RemoveItemTo(TArray<FInventoryData*>& target, UItemData* item, int count, bool withDelete)
{
    FInventoryData* targetData = HasItem(target, item->index, false);
    if (targetData) {
        if (targetData->ItemCount < count) {
            int tempCount = count - targetData->ItemCount;
            target.Remove(targetData);
            if (withDelete) delete targetData;
            RemoveItemTo(target, item, tempCount, withDelete);
        }
        else {
            targetData->ItemCount -= count;
        }
    }
}

FInventoryData* APlayerData::HasItem(TArray<FInventoryData*>& target, int itemIndex, bool checkMaxStack)
{
    for (FInventoryData* data : target) {
        if (data->ItemData->index == itemIndex) {
            if (checkMaxStack) {
                if (data->ItemCount < data->ItemData->maxStack) {
                    return data;
                }
            }
            else {
                return data;
            }
        }
    }

    return nullptr;
}

FInventoryData* APlayerData::FindItemWithLocation(TArray<FInventoryData*>& target, FVector2D location)
{
    for (FInventoryData* data : target) {
        if (data->SlotIndex == location) {
            return data;
        }
    }

    return nullptr;
}

TArray<FInventoryData*>& APlayerData::GetTargetContainer(EContainerCategory category)
{
    switch (category)
    {
    case EContainerCategory::Inventory:
        return PlayerInventory;
        break;
    case EContainerCategory::Storage:
        break;
    case EContainerCategory::Equipment:
        break;
    case EContainerCategory::Container:
        return Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController())->InteractObj->ContainerInventory;
        break;
    case EContainerCategory::Merchant:
        break;
    }

    return PlayerStorage;
}

void APlayerData::MoveItemIndex(TArray<FInventoryData*>& target, FVector2D from, FVector2D to)
{
    FInventoryData* targetData = FindItemWithLocation(target, from);
    if (targetData) {
        targetData->SlotIndex = to;
    }
}

void APlayerData::MoveItemIndex(TArray<FInventoryData*>& target, FVector2D to, FInventoryData* data)
{
    data->SlotIndex = to;
    target.Add(data);
}
