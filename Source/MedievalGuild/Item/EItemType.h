// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{ 
	Money UMETA(DisplayName = "Money"),
	Gold UMETA(DisplayName = "Gold"),
	Silver UMETA(DisplayName = "Silver"),
	Ruby UMETA(DisplayName = "Ruby"),
	Armor UMETA(DisplayName = "Armor"),
	Weapon UMETA(DisplayName = "Weapon"),
};
