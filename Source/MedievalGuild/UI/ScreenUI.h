// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "ScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UScreenUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void InitScreenUISetting();

	bool CheckAnyTextVisible();
	void SetInteractText(bool visible, FString text);
	void SetExtractText(bool visible, float value);
	void SetSystemMessage(bool visible, FString text);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractText;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ExtractObject;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExtractValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SystemMessage;
};
