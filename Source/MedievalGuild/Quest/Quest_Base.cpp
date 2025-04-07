// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Base.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestManager.h"
bool UQuest_Base::CanStartQuest()
{
    for (int PreQuestIndex : Quest->PreRequisiteQuests)
    {
        UQuest_Base* PreQuest = UQuestManager::GetInstance()->FindQuest(PreQuestIndex);
        if (PreQuest && PreQuest->GetQuestStatus() != EQuestStatus::Completed)
        {
            return false;
        }
    }

    return true;
}

void UQuest_Base::StartQuest(UWorld* World)
{
    if (CanStartQuest())
    {
        if (Quest->QuestStatus == EQuestStatus::NotStarted)
            Quest->QuestStatus = EQuestStatus::InProgress;

    }
}

void UQuest_Base::CancleQuest()
{
	if (Quest->QuestStatus == EQuestStatus::InProgress)
        Quest->QuestStatus = EQuestStatus::NotStarted;

}

void UQuest_Base::CompleteQuest()
{
    if (Quest->QuestStatus == EQuestStatus::InProgress)
    {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Quest Completed!"));
        Quest->QuestStatus = EQuestStatus::RewardPending;
    }
}

void UQuest_Base::QuestReward()
{
	if (Quest->QuestStatus == EQuestStatus::RewardPending)
	{
		Quest->QuestStatus = EQuestStatus::Completed;
	}
}

void UQuest_Base::SetQuestData(UQuestData_Base* InQuest)
{
    Quest = InQuest;
    Quest->AddToRoot();
}

void UQuest_Base::ClearQuest()
{
	if (Quest)
	{
		Quest->RemoveFromRoot();
	}
	Quest = nullptr;
}


void UQuest_Base::CheckQuest(int index)
{
    if (Quest->QuestIndex == index)
    {
        CompleteQuest();
    }
}

void UQuest_Base::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    if (!Quest)
    {
        UE_LOG(LogTemp, Error, TEXT("Quest data is null!"));
        return;
    }

    JsonObject->SetStringField(TEXT("QuestName"), Quest->QuestName);
    JsonObject->SetStringField(TEXT("Description"), Quest->Description);
    JsonObject->SetNumberField(TEXT("QuestIndex"), Quest->QuestIndex);
    JsonObject->SetNumberField(TEXT("QuestStatus"), static_cast<int32>(Quest->QuestStatus));
    JsonObject->SetNumberField(TEXT("QuestType"), static_cast<int32>(Quest->QuestType));
    JsonObject->SetNumberField(TEXT("RewardGold"), Quest->RewardGold);
    JsonObject->SetBoolField(TEXT("HasPlayer"), Quest->HasPlayer);


    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest->RewardItems)
    {
        if (PreQuest)
        {
            RewardItemJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest->index));
        }
    }
    JsonObject->SetArrayField(TEXT("RewardItems"), RewardItemJsonArray);

    TArray<TSharedPtr<FJsonValue>> RewardItemAmountJsonArray;
    for (int PreAmount : Quest->RewardItemAmount)
    {
        RewardItemAmountJsonArray.Add(MakeShared<FJsonValueNumber>(PreAmount));
    }
    JsonObject->SetArrayField(TEXT("RewardItemAmount"), RewardItemAmountJsonArray);

    TArray<TSharedPtr<FJsonValue>> PreRequisiteJsonArray;
    for (int PreQuest : Quest->PreRequisiteQuests)
    {
        PreRequisiteJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest));
    }
    JsonObject->SetArrayField(TEXT("PreRequisiteQuests"), PreRequisiteJsonArray);
}

void UQuest_Base::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest)
        {
            Quest = NewObject<UQuestData_Base>();
        }

        Quest->QuestName = JsonObject->GetStringField(TEXT("QuestName"));
        Quest->Description = JsonObject->GetStringField(TEXT("Description"));
        Quest->QuestIndex = JsonObject->GetIntegerField(TEXT("QuestIndex"));
        Quest->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField(TEXT("QuestStatus")));
        Quest->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField(TEXT("QuestType")));
        Quest->RewardGold = JsonObject->GetIntegerField(TEXT("RewardGold"));
        Quest->HasPlayer = JsonObject->GetBoolField(TEXT("HasPlayer"));

        const TArray<TSharedPtr<FJsonValue>>& RewardItemAmountJsonArray = JsonObject->GetArrayField(TEXT("RewardItemAmount"));
        Quest->RewardItemAmount.Empty(RewardItemAmountJsonArray.Num());
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemAmountJsonArray)
        {
            Quest->RewardItemAmount.Add(PreJsonValue->AsNumber());
        }

        const TArray<TSharedPtr<FJsonValue>>& RewardItemJsonArray = JsonObject->GetArrayField(TEXT("RewardItems"));
        Quest->RewardItems.Empty(RewardItemJsonArray.Num());
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemJsonArray)
        {
            int RewardItemIndex = PreJsonValue->AsNumber();
            UItemData* PreQuest = UItemDataManager::GetInstance()->FindItemData(RewardItemIndex);
            if (PreQuest)
            {
                Quest->RewardItems.Add(PreQuest);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Item data not found for index: %d"), RewardItemIndex);
            }
        }


        const TArray<TSharedPtr<FJsonValue>>& PreRequisiteJsonArray = JsonObject->GetArrayField(TEXT("PreRequisiteQuests"));
        Quest->PreRequisiteQuests.Empty(PreRequisiteJsonArray.Num());
        for (const TSharedPtr<FJsonValue>& PreJsonValue : PreRequisiteJsonArray)
        {
            int PreQuestIndex = PreJsonValue->AsNumber();
            Quest->PreRequisiteQuests.Add(PreQuestIndex);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid JSON object!"));
    }
}


EQuestStatus UQuest_Base::GetQuestStatus()
{
    return Quest->QuestStatus;
}

int UQuest_Base::GetQuestIndex()
{
    return Quest->QuestIndex;
}
