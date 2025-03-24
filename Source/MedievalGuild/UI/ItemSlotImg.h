// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "ItemSlotImg.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UItemSlotImg : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemSlot;
};
