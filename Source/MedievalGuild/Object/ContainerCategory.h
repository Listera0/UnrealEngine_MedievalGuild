#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EContainerCategory : uint8
{
	None,
	Inventory,
	Storage,
	Equipment,
	Container,
	Merchant
};
