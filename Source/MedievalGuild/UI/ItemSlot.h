// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPressedSlot();

	UFUNCTION()
	void OnReleasedSlot();
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* ItemSlot;

	UPROPERTY()
	UItemDragDropOperation* CurrentOperation;

	int SlotIndex;
};
