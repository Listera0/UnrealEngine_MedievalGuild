// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "GearWidget.h"

#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
						TSubclassOf<UUserWidget> gearWidget);

	void ShowContainer();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> GearWidget;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* HelmetSlot;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ClothSlot;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ShoesSlot;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* BagSlot;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* WeaponSlot;

	UGearWidget* Widget_Helmet;
	UGearWidget* Widget_Cloth;
	UGearWidget* Widget_Shoes;
	UGearWidget* Widget_Bag;
	UGearWidget* Widget_Weapon;
};
