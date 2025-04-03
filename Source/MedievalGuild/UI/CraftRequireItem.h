// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftRequireItem.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UCraftRequireItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItemInfo();
};
