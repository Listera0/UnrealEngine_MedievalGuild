// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestPlayerPanel.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "QuestSlot.h"

void UQuestPlayerPanel::QuestPlayerPanelInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass)
{
	QuestSlotClass = InitWidgetClass[0];

	QuestList.Add(this);
	ShowQuestList();
}

void UQuestPlayerPanel::ShowQuestList()
{
	QuestSlotGrid->ClearChildren();

	int TotalQuestCount = 0;
	for (UUserWidget* quest : QuestList) {
		UQuestSlot* newQuestSlot = CreateWidget<UQuestSlot>(GetWorld(), QuestSlotClass);
		FButtonStyle buttonStyle;
		FSlateBrush borderBrush;
		borderBrush.TintColor = FLinearColor(0.5f, 0.2f, 0.2f, 1.0f);
		borderBrush.DrawAs = ESlateBrushDrawType::Box;
		buttonStyle.SetNormal(borderBrush);
		buttonStyle.SetHovered(borderBrush);
		buttonStyle.SetPressed(borderBrush);
		buttonStyle.NormalPadding = 0.0f;
		buttonStyle.PressedPadding = 0.0f;
		newQuestSlot->QuestSlot->SetStyle(buttonStyle);

		UVerticalBoxSlot* GridSlot = QuestSlotGrid->AddChildToVerticalBox(newQuestSlot);
		GridSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f));
		GridSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		GridSlot->SetHorizontalAlignment(HAlign_Fill);
		GridSlot->SetVerticalAlignment(VAlign_Fill);

		TotalQuestCount++;
	}

	Cast<UCanvasPanelSlot>(QuestSlot->Slot)->SetSize(FVector2D(500.0f, (float)(TotalQuestCount) * 50.0f));
}
