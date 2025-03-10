// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "EquipmentWidget.h"
#include "PlayerContainerWidget.h"
#include "ContainerWidget.h"
#include "../Framework/GameManager.h"

#include "PlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerInventory(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void PlayerInventoryInitSetting();

protected:
	AGameManager* GameManager = nullptr;
	UBlueprintBindComponent* Blueprints = nullptr;

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InventorySlot;

	UEquipmentWidget* Widget_Equipment;
	UPlayerContainerWidget* Widget_Inventory;
	UContainerWidget* Widget_Container;
};
