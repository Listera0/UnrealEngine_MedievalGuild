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
#include "TradeWidget.h"
#include "PlayerStorage.h"
#include "MerchantInventory.h"
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

	/// <summary>
	/// 0 = equip, inv, empty / 1 = equip, inv, con / 2 = equip, inv, storage / 3 = merchant, trade, storage
	/// </summary>
	void PanelVisibleSetting(int value);
	void PanelVisibleSetting(UUserWidget* widget, ESlateVisibility visible);

protected:
	AGameManager* GameManager = nullptr;
	UBlueprintBindComponent* Blueprints = nullptr;

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InventorySlot;

	UEquipmentWidget* Widget_Equipment;
	UPlayerContainerWidget* Widget_Inventory;
	UContainerWidget* Widget_Container;
	UTradeWidget* Widget_Trade;
	UPlayerStorage* Widget_Storage;
	UMerchantInventory* Widget_Merchant;
};
