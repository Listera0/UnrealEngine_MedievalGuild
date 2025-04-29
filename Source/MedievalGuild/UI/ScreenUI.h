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
	void SetDialogueText(bool visible, FString text);
	void ShowTutorialPanel(int index);
	UTextBlock* GetTutorialMessage(int index, int value);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ExtractObject = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExtractValue = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SystemMessage = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* DialogueBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* TutorialPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_1Text = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_2Text = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_3Text = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_4Text = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_5Text = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_1Text_1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_1Text_2 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_2Text_1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_2Text_2 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_3Text_1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_3Text_2 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_4Text_1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_4Text_2 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_5Text_1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tutorial_5Text_2 = nullptr;
};
