// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "ContainerWidget.h"

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

	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> EquipmentWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> ContainerWidget;

public:
	void PlayerInventoryInitSetting();

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* InventorySlot;
};
