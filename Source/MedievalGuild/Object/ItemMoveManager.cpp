// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMoveManager.h"

UItemMoveManager* UItemMoveManager::Instance = nullptr;

UItemMoveManager* UItemMoveManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UItemMoveManager>();
        Instance->AddToRoot();
    }
    return Instance;
}
