// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "ScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UScreenUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetInteractText(bool visible, FString text);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractText;
};
