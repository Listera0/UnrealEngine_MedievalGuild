// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Kill.h"
#include "../Item/ItemDataManager.h"

void UQuest_Kill::SetQuestData(UQuestData_Base* InQuest)
{
	Quest = static_cast<UQuestData_Kill*>(InQuest);
}

bool UQuest_Kill::CheckQuest(int index)
{
	if (Quest->ObjectIndex == index)
	{
		Quest->Amount++;
	}

	if (Quest->Amount >= Quest->RequiredAmount)
	{
		CompleteQuest();
		return true;
	}

	return false;
}

void UQuest_Kill::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest->QuestName);
    JsonObject->SetStringField("Description", Quest->Description);
    JsonObject->SetNumberField("QuestIndex", Quest->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest->RewardGold);

    JsonObject->SetNumberField("ObjectIndex", Quest->ObjectIndex);
    JsonObject->SetNumberField("RequiredAmount", Quest->RequiredAmount);
    JsonObject->SetNumberField("Amount", Quest->Amount);


    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest->RewardItems)
    {
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

void UQuest_Kill::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest)
            Quest = NewObject<UQuestData_Kill>();

        Quest->QuestName = JsonObject->GetStringField("QuestName");
        Quest->Description = JsonObject->GetStringField("Description");
        Quest->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest->RewardGold = JsonObject->GetIntegerField("RewardGold");
        Quest->ObjectIndex = JsonObject->GetIntegerField("ObjectIndex");
        Quest->RequiredAmount = JsonObject->GetIntegerField("RequiredAmount");
        Quest->Amount = JsonObject->GetIntegerField("Amount");

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
            if (PreQuest)
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

EQuestStatus UQuest_Kill::GetQuestStatus()
{
    return Quest->QuestStatus;
}

int UQuest_Kill::GetQuestIndex()
{
    return Quest->QuestIndex;
}
