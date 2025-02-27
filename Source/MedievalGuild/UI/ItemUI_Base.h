// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "ItemUI_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API UItemUI_Base : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	void SetItemCountText();
	void SetItemBind(TArray<UItemUI_Base*> items);

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCountText;

	int ItemCount;

	bool bStackable = false;

	TArray<UItemUI_Base*> BindItems;
};
