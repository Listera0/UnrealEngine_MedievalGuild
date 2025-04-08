// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInfoPanel.h"
#include "../Item/ItemDataManager.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Quest/Quest_Item.h"
#include "../Quest/Data/QuestData_Item.h"
#include "../Quest/Data/QuestData_Arrive.h"
#include "../Quest/Data/QuestData_Kill.h"

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

	if (SelectQuest->GetQuestData()->RewardItemAmount.Num() == 0) {
		RewardValue->SetText(FText::FromString(FString::Printf(TEXT("X"))));
	}
	else { 
		RewardValue->SetText(FText::FromString(FString::Printf(TEXT("%s  X %d"), 
			*UItemDataManager::GetInstance()->FindItemData(SelectQuest->GetQuestData()->RewardItems[0])->name, SelectQuest->GetQuestData()->RewardItemAmount[0])));
	}
}

void UQuestInfoPanel::CheckQuestProgress()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%d"), SelectQuest->GetQuestData()->QuestStatus));

	switch (SelectQuest->GetQuestStatus())
	{
		case EQuestStatus::NotStarted:
			TargetValue->SetColorAndOpacity(BasicColor);
			SetInteractButtonColor(BasicColor);
			ButtonText->SetText(FText::FromString("Accept"));
			break;
		case EQuestStatus::InProgress:
			TargetValue->SetColorAndOpacity(NotEnoughColor);
			SetInteractButtonColor(NotEnoughColor);
			ButtonText->SetText(FText::FromString("Cancel"));
			break;
		case EQuestStatus::RewardPending:
			TargetValue->SetColorAndOpacity(SuccessColor);
			SetInteractButtonColor(SuccessColor);
			ButtonText->SetText(FText::FromString("Success"));
			break;
		default:
			break;
	}

	if (SelectQuest->GetQuestData()->QuestType == EQuestType::Item) {
		UQuestData_Item* targetQuest = Cast<UQuestData_Item>(SelectQuest->GetQuestData());
		UItemData* itemData = UItemDataManager::GetInstance()->FindItemData(targetQuest->QuestItemIndex);
		TargetValue->SetText(FText::FromString(FString::Printf(TEXT("%s ( %d / %d )"), *itemData->name, 
			PlayerController->PlayerData->GetItemCount(itemData->index), targetQuest->RequiredAmount)));
	}
	else if (SelectQuest->GetQuestData()->QuestType == EQuestType::Arrive) {
		UQuestData_Arrive* targetQuest = Cast<UQuestData_Arrive>(SelectQuest->GetQuestData());
		TargetValue->SetText(FText::FromString(FString::Printf(TEXT("Locate location ( %d / 1 )"), SelectQuest->GetQuestStatus() == EQuestStatus::RewardPending ? 1 : 0)));
	}
	else if (SelectQuest->GetQuestData()->QuestType == EQuestType::KillCount) {
		UQuestData_Kill* targetQuest = Cast<UQuestData_Kill>(SelectQuest->GetQuestData());
		TargetValue->SetText(FText::FromString(FString::Printf(TEXT("Eliminate Target ( %d / 1 )"), SelectQuest->GetQuestStatus() == EQuestStatus::RewardPending ? 1 : 0)));
	}
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
	// 버튼을 하이드아웃에서만 누를수 있게
	if (PlayerController->CurrentPlayerLocation != "Hideout") return;

	switch (SelectQuest->GetQuestStatus())
	{
		case EQuestStatus::NotStarted:
			// 수락
			SelectQuest->StartQuest(GetWorld());
			break;
		case EQuestStatus::InProgress:
			// 취소

			break;
		case EQuestStatus::RewardPending:
			for (int i = 0; i < SelectQuest->GetQuestData()->RewardItems.Num(); i++) {
				FInventoryData* newItem = new FInventoryData(FVector2D(-1.0f), UItemDataManager::GetInstance()->FindItemData(SelectQuest->GetQuestData()->RewardItems[i]), SelectQuest->GetQuestData()->RewardItemAmount[i]);
				PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage),
					newItem, PlayerController->GetTargetContainer(EContainerCategory::Storage));
				PlayerController->ScreenUI->SetSystemMessage(true, FString::Printf(TEXT("Get %d %s"), newItem->ItemCount, *newItem->ItemData->name));
			}

			if (SelectQuest->GetQuestData()->QuestType == EQuestType::Item) {
				UQuestData_Item* targetQuest = Cast<UQuestData_Item>(SelectQuest->GetQuestData());
				UItemData* itemData = UItemDataManager::GetInstance()->FindItemData(targetQuest->QuestItemIndex);
				int leftCount = PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Inventory), itemData, targetQuest->RequiredAmount, true);
				if (leftCount != 0) { PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), itemData, targetQuest->RequiredAmount, true); }
			}
			SelectQuest->QuestReward();
			ShowQuestDetail(nullptr);
			PlayerController->InventoryUI->Widget_QuestPlayerPanel->ShowQuestList();
			break;
		default:
			break;
	}
}
