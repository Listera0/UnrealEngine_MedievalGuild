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
        FString p = Quest->QuestName + FString::Printf(TEXT(" - Quest Is Completed!!"));
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, p);
        Quest->QuestStatus = EQuestStatus::Completed;
        QuestReward();
    }
}

void UQuest_Base::QuestReward()
{   
    if (Quest->RewardGold != 0)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
    }
}

void UQuest_Base::SetQuestData(UQuestData_Base* InQuest)
{
    Quest = InQuest;
}


bool UQuest_Base::CheckQuest(int index)
{
	return false;
}

void UQuest_Base::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest->QuestName);
    JsonObject->SetStringField("Description", Quest->Description);
    JsonObject->SetNumberField("QuestIndex", Quest->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest->RewardGold);
    JsonObject->SetBoolField("HasPlayer", Quest->HasPlayer);

    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest->RewardItems)
    {
        if (PreQuest)
         RewardItemJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest->index));
    }
    JsonObject->SetArrayField("RewardItems", RewardItemJsonArray);


    TArray<TSharedPtr<FJsonValue>> RewardItemAmountJsonArray;
    for (int PreAmount : Quest->RewardItemAmount)
    {
        RewardItemAmountJsonArray.Add(MakeShared<FJsonValueNumber>(PreAmount));
    }
    JsonObject->SetArrayField("RewardItemAmount", RewardItemAmountJsonArray);

    TArray<TSharedPtr<FJsonValue>> PreRequisiteJsonArray;
    for (int PreQuest : Quest->PreRequisiteQuests)
    {
        PreRequisiteJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest));
    }
    JsonObject->SetArrayField("PreRequisiteQuests", PreRequisiteJsonArray);
}

void UQuest_Base::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if(!Quest)
            Quest = NewObject<UQuestData_Base>();

        Quest->QuestName = JsonObject->GetStringField("QuestName");
        Quest->Description = JsonObject->GetStringField("Description");
        Quest->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest->RewardGold = JsonObject->GetIntegerField("RewardGold");
        Quest->HasPlayer = JsonObject->GetBoolField("HasPlayer");

        const TArray<TSharedPtr<FJsonValue>>& RewardItemAmountJsonArray = JsonObject->GetArrayField("RewardItemAmount");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemAmountJsonArray)
        {
            int RewardItemAmount = PreJsonValue->AsNumber();
            Quest->RewardItemAmount.Add(RewardItemAmount);
        }

        const TArray<TSharedPtr<FJsonValue>>& RewardItemJsonArray = JsonObject->GetArrayField("RewardItems");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemJsonArray)
        {
            int RewardItemIndex = PreJsonValue->AsNumber();
            UItemData* PreQuest = UItemDataManager::GetInstance()->FindItemData(RewardItemIndex);
            if(PreQuest)
                Quest->RewardItems.Add(PreQuest);
        }

        const TArray<TSharedPtr<FJsonValue>>& PreRequisiteJsonArray = JsonObject->GetArrayField("PreRequisiteQuests");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : PreRequisiteJsonArray)
        {
            int PreQuestIndex = PreJsonValue->AsNumber();
            Quest->PreRequisiteQuests.Add(PreQuestIndex);
        }
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
