// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUI.h"


void UScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitScreenUISetting();
}

void UScreenUI::InitScreenUISetting()
{
	InteractText->SetVisibility(ESlateVisibility::Collapsed);
	ExtractObject->SetVisibility(ESlateVisibility::Collapsed);
	SystemMessage->SetVisibility(ESlateVisibility::Collapsed);
	DialogueBox->SetVisibility(ESlateVisibility::Collapsed);
	TutorialPanel->SetVisibility(ESlateVisibility::Collapsed);
}

bool UScreenUI::CheckAnyTextVisible()
{
	if (InteractText->GetVisibility() == ESlateVisibility::Visible ||
		ExtractObject->GetVisibility() == ESlateVisibility::Visible || 
		SystemMessage->GetVisibility() == ESlateVisibility::Visible ||
		DialogueBox->GetVisibility() == ESlateVisibility::Visible ||
		TutorialPanel->GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Visible);
		return true;
	}

	SetVisibility(ESlateVisibility::Collapsed);
	return false;
}

void UScreenUI::SetInteractText(bool visible, FString text)
{
	InteractText->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	InteractText->SetText(FText::FromString(text));
	CheckAnyTextVisible();
}

void UScreenUI::SetExtractText(bool visible, float value)
{
	ExtractObject->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	ExtractValue->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), value)));
	CheckAnyTextVisible();
}

void UScreenUI::SetSystemMessage(bool visible, FString text)
{
	SystemMessage->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	SystemMessage->SetText(FText::FromString(text));
	CheckAnyTextVisible();

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]()
	{
		SystemMessage->SetVisibility(ESlateVisibility::Collapsed);
		SystemMessage->SetText(FText::FromString(""));
		CheckAnyTextVisible();
	}, 2.0f, false);
}

void UScreenUI::SetDialogueText(bool visible, FString text)
{
	DialogueBox->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	DialogueText->SetText(FText::FromString(text));
	CheckAnyTextVisible();
}

void UScreenUI::ShowTutorialPanel(int index)
{
	TutorialPanel->SetVisibility(index != -1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	CheckAnyTextVisible();
	if (index == -1) return;

	for (int i = 1; i < TutorialPanel->GetAllChildren().Num(); i++) {
		TutorialPanel->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
	}
	Cast<UCanvasPanel>(TutorialPanel->GetChildAt(index))->SetVisibility(ESlateVisibility::Visible);
	CheckAnyTextVisible();
}

UTextBlock* UScreenUI::GetTutorialMessage(int index, int value)
{
	switch (index)
	{
		case 0: 
			switch (value)
			{
				case 0: return Tutorial_1Text; break;
				case 1: return Tutorial_1Text_1; break;
				case 2: return Tutorial_1Text_2; break;
			}
			break;
		case 1: 
			switch (value)
			{
				case 0: return Tutorial_2Text; break;
				case 1: return Tutorial_2Text_1; break;
				case 2: return Tutorial_2Text_2; break;
			}
			break;
		case 2:
			switch (value)
			{
				case 0: return Tutorial_3Text; break;
				case 1: return Tutorial_3Text_1; break;
				case 2: return Tutorial_3Text_2; break;
			}
			break;
		case 3: 
			switch (value)
			{
				case 0: return Tutorial_4Text; break;
				case 1: return Tutorial_4Text_1; break;
				case 2: return Tutorial_4Text_2; break;
			}
			break;
		case 4: 
			switch (value)
			{
				case 0: return Tutorial_5Text; break;
				case 1: return Tutorial_5Text_1; break;
				case 2: return Tutorial_5Text_2; break;
			}
			break;
	}

	return Tutorial_1Text;
}
