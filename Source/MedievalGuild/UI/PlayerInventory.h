// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "../Framework/GameManager.h"
#include "EquipmentWidget.h"
#include "PlayerContainerWidget.h"
#include "ContainerWidget.h"
#include "TradeWidget.h"
#include "PlayerStorage.h"
#include "MerchantInventory.h"
#include "QuestPlayerPanel.h"
#include "QuestInfoPanel.h"
#include "OptionMenu.h"
#include "StageMap.h"

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
	/// 0 >> Normal Tab || 1 >> Container || 2 >> Storage || 3 >> Merchant || 4 >> Quest-Mer || 5 >> Quest-Inv
	/// </summary>
	void PanelVisibleSetting(int value);
	void AllPanelCollapsed();
	void PanelVisibleSetting(UUserWidget* widget, ESlateVisibility visible);
	void PanelOpenSetting(UUserWidget* widget);

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InventorySlot;

	UEquipmentWidget* Widget_Equipment;
	UPlayerContainerWidget* Widget_Inventory;
	UContainerWidget* Widget_Container;
	UTradeWidget* Widget_Trade;
	UPlayerStorage* Widget_Storage;
	UMerchantInventory* Widget_Merchant;
	UQuestPlayerPanel* Widget_QuestPlayerPanel;
	UQuestInfoPanel* Widget_QuestInfoPanel;
	UOptionMenu* Widget_OptionMenu;
	UStageMap* Widget_StageMap;

protected:
	class APlayerCharacterController* PlayerController = nullptr;
	AGameManager* GameManager = nullptr;
	UBlueprintBindComponent* Blueprints = nullptr;
};
