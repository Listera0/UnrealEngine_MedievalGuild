// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "../Framework/PlayerCharacterController.h"

APlayerData::APlayerData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    QuestCompo = CreateDefaultSubobject<UQuestComponent>(FName("Quest Component"));
}

void APlayerData::AddItemToAllWork(TArray<FInventoryData*>& target, FInventoryData* item, UContainer_Base* targetContainer)
{
    FInventoryData* hasitem = HasItem(target, item->ItemData->index, true);
    if (hasitem) {
        int value = hasitem->ItemData->maxStack - hasitem->ItemCount;
        if (value < item->ItemCount) {
            hasitem->ItemCount += value;
            item->ItemCount = value - item->ItemCount;
            AddItemToAllWork(target, item, targetContainer);
        }
        else {
            hasitem->ItemCount += item->ItemCount;
        }
    }
    else {
        FVector2D findLocation = targetContainer->FindEmptySlot(FVector2D(item->ItemData->width, item->ItemData->height));
        if (findLocation != FVector2D(-1.0f)) {
            item->SlotIndex = findLocation;
            target.Add(item);
        }
    }
}

void APlayerData::AddItemTo(TArray<FInventoryData*>& target, FInventoryData* item)
{
    FInventoryData* targetData = HasItem(target, item->ItemData->index, true);
    if (!targetData) { target.Add(item); }

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
    FInventoryData* targetData = FindItemWithLocation(target, location);
    if (targetData) {
        target.Remove(targetData);
        if (withDelete) delete targetData;
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
        case EContainerCategory::Inventory: return PlayerInventory; break;
        case EContainerCategory::Storage: return PlayerStorage; break;
        case EContainerCategory::Trade: return PlayerTrade; break;
        case EContainerCategory::Container:
            return Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController())->InteractObj->ContainerInventory; break;
        case EContainerCategory::Merchant:
            //return Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController())->InteractObj->ContainerInventory;
            break;
        case EContainerCategory::Helmet:
        case EContainerCategory::Cloth:
        case EContainerCategory::Shoes:
        case EContainerCategory::Bag:
        case EContainerCategory::Weapon: return PlayerEquipment; break;
    }

    return PlayerStorage;
}

int APlayerData::GetEquipmentIndex(EContainerCategory category)
{
    int returnValue = -1;

    switch (category) {
        case EContainerCategory::Helmet: returnValue = 0; break;
        case EContainerCategory::Cloth: returnValue = 1; break;
        case EContainerCategory::Shoes: returnValue = 2; break;
        case EContainerCategory::Bag: returnValue = 3; break;
        case EContainerCategory::Weapon: returnValue = 4; break;
    }

    return returnValue;
}

int APlayerData::GetPlayerCurrency()
{
    int value = 0;
    for (FInventoryData* data : PlayerStorage) {
        if (data->ItemData->index == 0) {
            value += data->ItemCount;
        }
    }
    return value;
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
