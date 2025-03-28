// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoPanel.h"
#include "../Framework/PlayerCharacterController.h"

void UQuestInfoPanel::QuestInfoInitSetting()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	QuestInteractButton->OnClicked.AddDynamic(this, &UQuestInfoPanel::OnClickInteractButton);
}

void UQuestInfoPanel::ShowQuestDetail(UButton* Temp)
{
	if (Temp == nullptr) {
		QuestDetailPanel->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	QuestDetailPanel->SetVisibility(ESlateVisibility::Visible);
	// SelectQuest = data;
	QuestName->SetText(FText::FromString("Name"));
	QuestInfo->SetText(FText::FromString("Info"));
	CheckQuestProgress();
	RewardValue->SetText(FText::FromString(FString::Printf(TEXT("Reward"))));
}

void UQuestInfoPanel::CheckQuestProgress()
{
	if (CheckApplyQuest() && CheckSuccessQuest()) { TargetValue->SetColorAndOpacity(SuccessColor); }
	else { TargetValue->SetColorAndOpacity(NotEnoughColor); }
	TargetValue->SetText(FText::FromString(FString::Printf(TEXT("Target ( %d / %d )"), 0, 0)));
	SetInteractButton();
}

void UQuestInfoPanel::SetInteractButton()
{
	QuestInteractButton->SetColorAndOpacity(BasicColor);
	ButtonText->SetText(FText::FromString("Accept"));
	QuestInteractButton->SetColorAndOpacity(NotEnoughColor);
	ButtonText->SetText(FText::FromString("Cancel"));
	QuestInteractButton->SetColorAndOpacity(SuccessColor);
	ButtonText->SetText(FText::FromString("Success"));
}

bool UQuestInfoPanel::CheckApplyQuest()
{
	return false;
}

bool UQuestInfoPanel::CheckSuccessQuest()
{
	return false;
}

void UQuestInfoPanel::OnClickInteractButton()
{
	//if(CheckSuccessQuest())
	// getreward, state change remove quest
}
