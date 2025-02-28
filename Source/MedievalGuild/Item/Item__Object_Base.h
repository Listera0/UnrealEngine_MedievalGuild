#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EItemType.h"  // Assuming EItemType is an enumeration for item types

#include "Item__Object_Base.generated.h"

/**
 *  A base class to define item data.
 */
UCLASS(Blueprintable)
class MEDIEVALGUILD_API UItem__Object_Base : public UObject
{
	GENERATED_BODY()

public:
	// Constructor to initialize default values
	UItem__Object_Base();

	// Function to handle item-specific functionality (override this in subclasses if needed)
	virtual void ItemFunc();

	// Getter methods
	inline EItemType GetItemType() const { return eItemType; }
	inline float GetPrice() const { return price; }
	inline FName GetName() const { return name; }
	inline FName GetDescription() const { return description; }
	inline int GetIndex() const { return index; }
	inline int GetCount() const { return count; }
	inline int GetHeight() const { return height; }
	inline int GetWeight() const { return weight; }

	// Function to sell an item, reducing its count
	inline bool Sell(int Count) { if (count - Count >= 0) { count -= Count; return true; } return false; }
	inline void SetCount(int Count) { count = Count; }

protected:
	// The type of item (Weapon, Armor, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EItemType eItemType;

	// The price of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float price;

	// The name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName name;

	// The description of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName description;

	// Unique identifier for the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int index;

	// The count of how many items exist
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int count = 0;

	// Height and weight values for the item (if applicable)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int height = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int weight = 1;
};
