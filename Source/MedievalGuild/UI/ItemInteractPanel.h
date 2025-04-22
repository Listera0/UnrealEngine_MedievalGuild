// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Container_Base.h"
#include "../Object/InventoryData.h"

#include "ItemInteractPanel.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemInteractPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION() 
	void ShowInformationPanel();
	UFUNCTION()
	void EquipItem();
	UFUNCTION() 
	void UseItem();
	UFUNCTION() 
	void TrashItem();
	
public:
	class APlayerCharacterController* PlayerController = nullptr;
	FInventoryData* InteractItem = nullptr;
	EContainerCategory InteractContainer;

	void ShowPanelSetting(FVector2D Scale);

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* OwnerPanel;
	UPROPERTY(meta = (BindWidget))
	UButton* Information;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InformationText;
	UPROPERTY(meta = (BindWidget))
	UButton* Equip;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EquipText;
	UPROPERTY(meta = (BindWidget))
	UButton* Use;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UseText;
	UPROPERTY(meta = (BindWidget))
	UButton* Trash;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TrashText;
};
