// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoPanel.h"
#include "../Framework/PlayerCharacterController.h"

void UQuestInfoPanel::QuestInfoInitSetting()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	BasicColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);
	SuccessColor = FLinearColor(0.2f, 0.5f, 0.2f, 1.0f);
	NotEnoughColor = FLinearColor(0.5f, 0.2f, 0.2f, 1.0f);

	QuestInteractButton->OnClicked.AddDynamic(this, &UQuestInfoPanel::OnClickInteractButton);
}

void UQuestInfoPanel::ShowQuestDetail(UQuest_Base* data)
{
	if (data == nullptr) {
		SelectQuest = nullptr;
		QuestDetailPanel->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	QuestDetailPanel->SetVisibility(ESlateVisibility::Visible);
	SelectQuest = data;
	QuestName->SetText(FText::FromString(data->GetQuestData()->QuestName));
	QuestInfo->SetText(FText::FromString(data->GetQuestData()->Description));
	CheckQuestProgress();

	RewardValue->SetText(FText::FromString(FString::Printf(TEXT("Reward"))));
}

void UQuestInfoPanel::CheckQuestProgress()
{
	if (CheckApplyQuest()) {
		if (CheckSuccessQuest()) {
			TargetValue->SetColorAndOpacity(SuccessColor);
			SetInteractButtonColor(SuccessColor);
			ButtonText->SetText(FText::FromString("Success"));
		}
		else {
			TargetValue->SetColorAndOpacity(NotEnoughColor);
			SetInteractButtonColor(NotEnoughColor);
			ButtonText->SetText(FText::FromString("Cancel"));
		}
	}
	else {
		TargetValue->SetColorAndOpacity(BasicColor);
		SetInteractButtonColor(BasicColor);
		ButtonText->SetText(FText::FromString("Accept"));
	}
	
	TargetValue->SetText(FText::FromString(FString::Printf(TEXT("Target ( %d / %d )"), 0, 0)));
}

bool UQuestInfoPanel::CheckApplyQuest()
{
	return SelectQuest->GetQuestData()->HasPlayer;
}

bool UQuestInfoPanel::CheckSuccessQuest()
{
	// RewardPending
	if (SelectQuest->GetQuestStatus() == EQuestStatus::Completed) {
		return true;
	}

	return true; // temp
}

void UQuestInfoPanel::SetInteractButtonColor(FLinearColor color)
{
	FButtonStyle buttonStyle;
	FSlateBrush borderBrush;
	FSlateBrushOutlineSettings outlineBrush;

	outlineBrush.CornerRadii = FVector4(4.0f, 4.0f, 4.0f, 4.0f);
	outlineBrush.RoundingType = ESlateBrushRoundingType::FixedRadius;
	outlineBrush.Width = 1.0f;

	borderBrush.TintColor = FSlateColor(color);
	borderBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	borderBrush.OutlineSettings = outlineBrush;

	buttonStyle.SetNormal(borderBrush);
	buttonStyle.SetHovered(borderBrush);
	buttonStyle.SetPressed(borderBrush);
	buttonStyle.NormalPadding = 0.0f;
	buttonStyle.PressedPadding = 0.0f;
	QuestInteractButton->SetStyle(buttonStyle);
}

void UQuestInfoPanel::OnClickInteractButton()
{
	if (!CheckSuccessQuest()) { return; }

	for (int i = 0; i < SelectQuest->GetQuestData()->RewardItems.Num(); i++) {
		FInventoryData* newItem = new FInventoryData(FVector2D(-1.0f), SelectQuest->GetQuestData()->RewardItems[i], SelectQuest->GetQuestData()->RewardItemAmount[i]);
		PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage),
			newItem, PlayerController->GetTargetContainer(EContainerCategory::Storage));
		SelectQuest->QuestReward();
	}
}
