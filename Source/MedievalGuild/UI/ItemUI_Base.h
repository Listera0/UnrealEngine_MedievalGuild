// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Object/InventoryData.h"

#include "ItemUI_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API UItemUI_Base : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	inline void SetItemData(FInventoryData* data) { ItemData = data; }
	inline void SetItemIndex(FVector2D index) { ItemIndex = index; }
	inline void SetItemBind(TArray<UItemUI_Base*> items) { BindItems.Empty(); BindItems.Append(items); }
	void SetItemCountText();

	UItemUI_Base* GetOwnerItem();
	UItemUI_Base* GetCountItem();

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemCountText;

	FInventoryData* ItemData;
	FVector2D ItemIndex;
	TArray<UItemUI_Base*> BindItems;
};
