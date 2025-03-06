// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContainerEnum.generated.h"

UENUM(BlueprintType)
enum class EContainerEnum : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	Inventory	UMETA(DisplayName = "Inventory"),
	Container	UMETA(DisplayName = "Container"),
	Helmet		UMETA(DisplayName = "Helmet")
};