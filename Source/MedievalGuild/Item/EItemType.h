// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Consumeable,
	Currency,
	Helmet,
	Cloth,
	Shoes,
	Bag,
	Weapon
};
