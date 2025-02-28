// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "ItemUI_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API UItemUI_Base : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetItemCount(int count);
	void SetItemCountText();
	void SetItemBind(TArray<UItemUI_Base*> items);
	void SetDuplicateInit(UItemUI_Base* target);
	void SetItemIndex(int x, int y);
	void SetItemSize(int x, int y);

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCountText;

	int ItemCount;

	bool bStackable = false;

	TArray<UItemUI_Base*> BindItems;
	int ItemIndexX; int ItemIndexY;
	int ItemSizeX; int ItemSizeY;
};
