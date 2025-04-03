// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "../Object/InventoryData.h"
#include "CraftRequire.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UCraftRequire : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void CraftRequireInitSetting(TSubclassOf<UUserWidget> requireItem);
	void ResetRequireList();
	void ShowRequireList(FInventoryData* data);
	bool CheckSatisfiedRequire();
	void CraftButtonSetting(FLinearColor color);
	UFUNCTION()
	void CreateItem();

	TSubclassOf<UUserWidget> CraftRequireItemClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ItemList = nullptr;
	UPROPERTY(meta=(BindWidget))
	UButton* CraftButton = nullptr;

	FInventoryData* SelectItemData;
	FLinearColor NotEnoughColor;
	FLinearColor EnoughColor;
};
