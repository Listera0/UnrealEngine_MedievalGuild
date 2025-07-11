// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/PlayerSave.h"

APlayerData::APlayerData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    QuestCompo = CreateDefaultSubobject<UQuestComponent>(FName("Quest Component"));
}

bool APlayerData::CheckHasItem(int index, int count)
{
    int hasCount = 0;

    for (FInventoryData* data : PlayerInventory) {
        if (data->ItemData->index == index) {
            hasCount += data->ItemCount;
            if (hasCount >= count) return true;
        }
    }

    for (FInventoryData* data : PlayerStorage) {
        if (data->ItemData->index == index) {
            hasCount += data->ItemCount;
            if (hasCount >= count) return true;
        }
    }

    return false;
}

void APlayerData::AddItemToAllWork(TArray<FInventoryData*>& target, FInventoryData* item, UContainer_Base* targetContainer)
{
    FInventoryData* hasitem = HasItem(target, item->ItemData->index, true);
    if (hasitem) {
        int value = hasitem->ItemData->maxStack - hasitem->ItemCount;
        if (value < item->ItemCount) {
            hasitem->ItemCount += value;
            item->ItemCount -= value;
            AddItemToAllWork(target, item, targetContainer);
        }
        else {
            hasitem->ItemCount += item->ItemCount;
        }
    }
    else {
        FVector2D findLocation = FindEmptySlot(target, targetContainer, item);
        if (findLocation != FVector2D(-1.0f)) {
            item->SlotIndex = findLocation;
            if (item->ItemData->maxStack < item->ItemCount) {
                int value = item->ItemCount - item->ItemData->maxStack;
                item->ItemCount = item->ItemData->maxStack;
                target.Add(item);

                FInventoryData* newData = new FInventoryData(FVector2D(-1.0f), item->ItemData, value);
                AddItemToAllWork(target, newData, targetContainer);
            }
            else {
                target.Add(item);
            }
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
            if (targetData->ItemCount <= 0) target.Remove(targetData);
            if (withDelete) delete targetData;
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

int APlayerData::RemoveItemTo(TArray<FInventoryData*>& target, UItemData* item, int count, bool withDelete)
{
    FInventoryData* targetData = HasItem(target, item->index, false);
    if (targetData) {
        int leftCount = 0;
        if (targetData->ItemCount < count) {
            leftCount = count - targetData->ItemCount;
            target.Remove(targetData);
            if (withDelete) delete targetData;
            leftCount = RemoveItemTo(target, item, leftCount, withDelete);
        }
        else {
            targetData->ItemCount -= count;
            if (targetData->ItemCount <= 0) {
                target.Remove(targetData);
                if (withDelete) delete targetData;
            }
        }
        return leftCount;
    }
    else {
        return count;
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

FVector2D APlayerData::FindEmptySlot(TArray<FInventoryData*>& target, UContainer_Base* targetPanel, FInventoryData* targetItem)
{

    TArray<FVector2D> alreadyInSlot;
    for (FInventoryData* data : target) {
        for (int j = 0; j < data->ItemData->height; j++) {
            for (int i = 0; i < data->ItemData->width; i++) {
                alreadyInSlot.Add(FVector2D((int)(data->SlotIndex.X) + i, (int)(data->SlotIndex.Y) + j));
            }
        }
    }

    for (int j = 0; j < (int)(targetPanel->ContainerSize.Y); j++) {
        for (int i = 0; i < (int)(targetPanel->ContainerSize.X); i++) {
            if (ContainsTArray(alreadyInSlot, FVector2D(i, j))) continue;
            if (i + targetItem->ItemData->width - 1 < targetPanel->ContainerSize.X && j + targetItem->ItemData->height - 1 < targetPanel->ContainerSize.Y) {
                bool bFindSlot = true;
                for (int p = 0; p < targetItem->ItemData->height; p++) {
                    for (int k = 0; k < targetItem->ItemData->width; k++) {
                        if (ContainsTArray(alreadyInSlot, FVector2D(i + k, j + p))) {
                            bFindSlot = false;
                            break;
                        }
                    }
                    if (!bFindSlot) break;
                }
                if (bFindSlot) return FVector2D((float)(i), (float)(j));
            }
        }
    }

    return FVector2D(-1.0f);
}

bool APlayerData::ContainsTArray(TArray<FVector2D> slot, FVector2D target)
{
    for (FVector2D data : slot) {
        if (data.X == target.X && data.Y == target.Y) return true;
    }

    return false;
}

TArray<FInventoryData*>& APlayerData::GetTargetContainer(EContainerCategory category)
{
    if (PlayerController == nullptr) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

    switch (category)
    {
        case EContainerCategory::Inventory: return PlayerInventory; break;
        case EContainerCategory::Storage: return PlayerStorage; break;
        case EContainerCategory::Trade: return PlayerTrade; break;
        case EContainerCategory::Container:
        case EContainerCategory::Merchant:
        case EContainerCategory::CraftInventory: return PlayerController->InteractObj->ContainerInventory; break;
        case EContainerCategory::EnemyInventory: return PlayerController->InteractCharacter->EnemyInventory; break;
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

int APlayerData::GetEquipmentIndex(EItemType category)
{
    int returnValue = -1;

    switch (category) {
    case EItemType::Helmet: returnValue = 0; break;
    case EItemType::Cloth: returnValue = 1; break;
    case EItemType::Shoes: returnValue = 2; break;
    case EItemType::Bag: returnValue = 3; break;
    case EItemType::Weapon: returnValue = 4; break;
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

int APlayerData::GetItemCount(int index)
{
    int totalCount = 0;

    for (FInventoryData* data : PlayerInventory) {
        if (data->ItemData->index == index) {
            totalCount += data->ItemCount;
        }
    }

    for (FInventoryData* data : PlayerStorage) {
        if (data->ItemData->index == index) {
            totalCount += data->ItemCount;
        }
    }

    return totalCount;
}

void APlayerData::SaveGame()
{
    UPlayerSave* SaveGameInstance = Cast<UPlayerSave>(UGameplayStatics::CreateSaveGameObject(UPlayerSave::StaticClass()));

    if (SaveGameInstance)
    {
        // Save Data
        SaveGameInstance->RecordSaveBaseData(0, PlayerName, PlayerHealth, PlayerStemina, PlayerEnergy);
        SaveGameInstance->RecordSaveItemData(PlayerInventory, PlayerStorage, PlayerEquipment);

        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveData"), 0);
    }
}

void APlayerData::LoadGame(int index)
{
    UPlayerSave* LoadGameInstance = Cast<UPlayerSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveData"), index));

    if (!LoadGameInstance) return;

    // Load Data
    LoadGameInstance->ExtractSaveBaseData(PlayerName, PlayerHealth, PlayerStemina, PlayerEnergy);
    LoadGameInstance->ExtractSaveItemData(PlayerInventory, PlayerStorage, PlayerEquipment);

    FTimerHandle timer;
    GetWorld()->GetTimerManager().SetTimer(timer, [this]() {
        if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
        PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
    }, 0.5f, false);
}

void APlayerData::RemoveSave()
{
    UGameplayStatics::DeleteGameInSlot("PlayerSaveData", 0);
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

void APlayerData::EmptyInventory()
{
    if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

    PlayerInventory.Empty();
    PlayerEquipment.Empty();
    PlayerEquipment.Init(nullptr, 5);
    PlayerController->InventoryUI->Widget_Equipment->UpdateWeapon();
}

void APlayerData::EmptyStorage()
{
    PlayerStorage.Empty();
}
