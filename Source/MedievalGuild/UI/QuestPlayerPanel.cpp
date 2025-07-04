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

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%d"), PlayerQuestList.Num()));
	PlayerQuestList.Empty();
	PlayerController->PlayerCharacter->QuestComponent->GetMyQuestDatas(PlayerQuestList);
	//UE_LOG(LogTemp, Warning, TEXT("컴포넌트 주소 : %d"), PlayerController->PlayerCharacter->QuestComponent);
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%d"), PlayerQuestList.Num()));


	int TotalQuestCount = 0;
	int CurrentQuestCount = 0;
	for (UQuest_Base* quest : PlayerQuestList) {
		if (quest->GetQuestStatus() == EQuestStatus::Completed) {
			TotalQuestCount++;
			continue; 
		}

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
		newQuestSlot->SetQuestInfo(PlayerController->TSManager->TranslateTexts(FText::FromString(quest->GetQuestData()->QuestName)));

		UVerticalBoxSlot* GridSlot = QuestSlotGrid->AddChildToVerticalBox(newQuestSlot);
		GridSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f));
		GridSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		GridSlot->SetHorizontalAlignment(HAlign_Fill);
		GridSlot->SetVerticalAlignment(VAlign_Fill);

		newQuestSlot->QuestIndex = TotalQuestCount;
		newQuestSlot->QuestSlot->OnClicked.AddDynamic(newQuestSlot, &UQuestSlot::ShowQuestDetail);

		TotalQuestCount++;
		CurrentQuestCount++;
	}

	Cast<UCanvasPanelSlot>(QuestSlot->Slot)->SetSize(FVector2D(500.0f, (float)(CurrentQuestCount) * 50.0f));
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
