// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CraftRequireItem.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UCraftRequireItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UImage* Image;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Count;

	void SetItemInfo(int index, int ownCount, int requireCount);
};
