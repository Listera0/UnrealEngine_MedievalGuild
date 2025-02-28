// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Base.h"

bool UQuest_Base::CanStartQuest()
{
    for (UQuest_Base* PreQuest : PreRequisiteQuests)
    {
        if (PreQuest && PreQuest->QuestStatus != EQuestStatus::Completed)
        {
            return false;
        }
    }

    return true;
}

void UQuest_Base::StartQuest()
{
    if (CanStartQuest())
    {
        if (QuestStatus == EQuestStatus::NotStarted)
            QuestStatus = EQuestStatus::InProgress;
    }
}

void UQuest_Base::CancleQuest()
{
	if (QuestStatus == EQuestStatus::InProgress)
		QuestStatus = EQuestStatus::NotStarted;
}

void UQuest_Base::CompleteQuest()
{
	if (QuestStatus == EQuestStatus::InProgress)
		QuestStatus = EQuestStatus::Completed;
}

void UQuest_Base::QuestReward()
{
    if (RewardItem)
    {
        AItem_Base* NewItem = GetWorld()->SpawnActor<AItem_Base>(RewardItem);
        if (NewItem)
        {
            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            //APlayerCharacter* Player = Cast<APlayerCharacter>(PC->GetPawn());
            //if (Player)
            //{
            //    for(int i=0;i<RewardItemAmount;i++)
            //        Player->AddItemToInventory(NewItem);
            //}
        }
    }

    if (RewardGold != 0)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
    }
}


bool UQuest_Base::CheckQuest(int index)
{
	return false;
}
