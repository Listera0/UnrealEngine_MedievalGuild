// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSlot.h"
#include "../Framework/PlayerCharacterController.h"

void UQuestSlot::SetQuestInfo(FText name)
{
	QuestName->SetText(name);
}

void UQuestSlot::ShowQuestDetail()
{
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	PlayerController->InventoryUI->Widget_QuestInfoPanel->ShowQuestDetail(PlayerController->InventoryUI->Widget_QuestPlayerPanel->PlayerQuestList[QuestIndex]);
}
