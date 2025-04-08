// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestPlayerPanel.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Character/PlayerCharacter.h"
#include "QuestInfoPanel.h"
#include "QuestSlot.h"

void UQuestPlayerPanel::QuestPlayerPanelInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass)
{
	QuestSlotClass = InitWidgetClass[0];
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	BasicColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);
	SuccessColor = FLinearColor(0.3f, 0.8f, 0.3f, 1.0f);
	NotEnoughColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);
}

void UQuestPlayerPanel::ShowQuestList()
{
	QuestSlotGrid->ClearChildren();

	PlayerQuestList.Empty();
	PlayerController->PlayerCharacter->QuestComponent->GetMyQuestDatas(PlayerQuestList);

	int TotalQuestCount = 0;
	for (UQuest_Base* quest : PlayerQuestList) {
		if (quest->GetQuestStatus() == EQuestStatus::Completed) { continue; }

		UQuestSlot* newQuestSlot = CreateWidget<UQuestSlot>(GetWorld(), QuestSlotClass);
		FButtonStyle buttonStyle;
		FSlateBrush borderBrush;
		borderBrush.TintColor = GetQuestSlotColor(quest->GetQuestStatus());
		borderBrush.DrawAs = ESlateBrushDrawType::Box;
		buttonStyle.SetNormal(borderBrush);
		buttonStyle.SetHovered(borderBrush);
		buttonStyle.SetPressed(borderBrush);
		buttonStyle.NormalPadding = 0.0f;
		buttonStyle.PressedPadding = 0.0f;
		newQuestSlot->QuestSlot->SetStyle(buttonStyle);
		newQuestSlot->SetQuestInfo(FText::FromString(quest->GetQuestData()->QuestName));

		UVerticalBoxSlot* GridSlot = QuestSlotGrid->AddChildToVerticalBox(newQuestSlot);
		GridSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f));
		GridSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		GridSlot->SetHorizontalAlignment(HAlign_Fill);
		GridSlot->SetVerticalAlignment(VAlign_Fill);

		newQuestSlot->QuestIndex = TotalQuestCount;
		newQuestSlot->QuestSlot->OnClicked.AddDynamic(newQuestSlot, &UQuestSlot::ShowQuestDetail);

		TotalQuestCount++;
	}

	Cast<UCanvasPanelSlot>(QuestSlot->Slot)->SetSize(FVector2D(500.0f, (float)(TotalQuestCount) * 50.0f));
}

FLinearColor UQuestPlayerPanel::GetQuestSlotColor(EQuestStatus status)
{
	FLinearColor returnColor = BasicColor;
	switch (status)
	{
	case EQuestStatus::NotStarted:
		break;
	case EQuestStatus::InProgress:
		break;
	case EQuestStatus::RewardPending:
		returnColor = SuccessColor;
		break;
	case EQuestStatus::Completed:
	default:
		break;
	}

	return returnColor;
}
