// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoPanel.h"
#include "../Item/ItemDataManager.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Quest/Quest_Item.h"
#include "../Quest/Data/QuestData_Item.h"

void UQuestInfoPanel::QuestInfoInitSetting()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	BasicColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);
	SuccessColor = FLinearColor(0.3f, 0.8f, 0.3f, 1.0f);
	NotEnoughColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);

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

	if (SelectQuest->GetQuestData()->QuestType == EQuestType::Item) {
		UQuestData_Item* targetQuest = Cast<UQuestData_Item>(SelectQuest->GetQuestData());
		if (!targetQuest) {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Error1");
			return;
		}

		UItemData* itemData = UItemDataManager::GetInstance()->FindItemData(targetQuest->QuestItemIndex);

		if (!itemData) {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Error2");
			return;
		}

		TargetValue->SetText(FText::FromString(FString::Printf(TEXT("%s ( %d / %d )"), *itemData->name, PlayerController->PlayerData->GetItemCount(itemData->index), targetQuest->RequiredAmount)));
	}
}

bool UQuestInfoPanel::CheckApplyQuest()
{
	//return SelectQuest->GetQuestData()->QuestStatus == EQuestStatus::InProgress;
	return SelectQuest->GetQuestData()->HasPlayer;
}

bool UQuestInfoPanel::CheckSuccessQuest()
{
	if (SelectQuest->GetQuestStatus() == EQuestStatus::RewardPending) {
		return true;
	}

	return false;
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
		FInventoryData* newItem = new FInventoryData(FVector2D(-1.0f), UItemDataManager::GetInstance()->FindItemData(SelectQuest->GetQuestData()->RewardItems[i]), SelectQuest->GetQuestData()->RewardItemAmount[i]);
		PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage),
			newItem, PlayerController->GetTargetContainer(EContainerCategory::Storage));
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, "Finish Quest");

	// quest item remove
	// 버튼을 하이드아웃에서만 누를수 있게

	SelectQuest->QuestReward();
	ShowQuestDetail(nullptr);
	PlayerController->InventoryUI->Widget_QuestPlayerPanel->ShowQuestList();
}
