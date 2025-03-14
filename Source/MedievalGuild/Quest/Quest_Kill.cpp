// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Kill.h"
#include "../Item/ItemDataManager.h"

void UQuest_Kill::SetQuestData(UQuestData_Base* InQuest)
{
    Quest = InQuest;
	Quest_Kill = static_cast<UQuestData_Kill*>(InQuest);
}

bool UQuest_Kill::CheckQuest(int index)
{
	if (Quest_Kill->ObjectIndex == index)
	{
		Quest_Kill->Amount++;
	}

	if (Quest_Kill->Amount >= Quest_Kill->RequiredAmount)
	{
		CompleteQuest();
		return true;
	}

	return false;
}

void UQuest_Kill::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest_Kill->QuestName);
    JsonObject->SetStringField("Description", Quest_Kill->Description);
    JsonObject->SetNumberField("QuestIndex", Quest_Kill->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest_Kill->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest_Kill->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest_Kill->RewardGold);

    JsonObject->SetNumberField("ObjectIndex", Quest_Kill->ObjectIndex);
    JsonObject->SetNumberField("RequiredAmount", Quest_Kill->RequiredAmount);
    JsonObject->SetNumberField("Amount", Quest_Kill->Amount);


    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest_Kill->RewardItems)
    {
        RewardItemJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest->index));
    }
    JsonObject->SetArrayField("RewardItems", RewardItemJsonArray);

    TArray<TSharedPtr<FJsonValue>> RewardItemAmountJsonArray;
    for (int PreAmount : Quest_Kill->RewardItemAmount)
    {
        RewardItemAmountJsonArray.Add(MakeShared<FJsonValueNumber>(PreAmount));
    }
    JsonObject->SetArrayField("RewardItemAmount", RewardItemAmountJsonArray);

    TArray<TSharedPtr<FJsonValue>> PreRequisiteJsonArray;
    for (int PreQuest : Quest_Kill->PreRequisiteQuests)
    {
        PreRequisiteJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest));
    }
    JsonObject->SetArrayField("PreRequisiteQuests", PreRequisiteJsonArray);
}

void UQuest_Kill::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest_Kill)
            Quest_Kill = NewObject<UQuestData_Kill>();

        Quest_Kill->QuestName = JsonObject->GetStringField("QuestName");
        Quest_Kill->Description = JsonObject->GetStringField("Description");
        Quest_Kill->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest_Kill->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest_Kill->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest_Kill->RewardGold = JsonObject->GetIntegerField("RewardGold");
        Quest_Kill->ObjectIndex = JsonObject->GetIntegerField("ObjectIndex");
        Quest_Kill->RequiredAmount = JsonObject->GetIntegerField("RequiredAmount");
        Quest_Kill->Amount = JsonObject->GetIntegerField("Amount");

        const TArray<TSharedPtr<FJsonValue>>& RewardItemAmountJsonArray = JsonObject->GetArrayField("RewardItemAmount");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemAmountJsonArray)
        {
            int RewardItemAmount = PreJsonValue->AsNumber();
            Quest_Kill->RewardItemAmount.Add(RewardItemAmount);
        }

        const TArray<TSharedPtr<FJsonValue>>& RewardItemJsonArray = JsonObject->GetArrayField("RewardItems");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemJsonArray)
        {
            int RewardItemIndex = PreJsonValue->AsNumber();
            UItemData* PreQuest = UItemDataManager::GetInstance()->FindItemData(RewardItemIndex);
            if (PreQuest)
                Quest_Kill->RewardItems.Add(PreQuest);
        }

        const TArray<TSharedPtr<FJsonValue>>& PreRequisiteJsonArray = JsonObject->GetArrayField("PreRequisiteQuests");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : PreRequisiteJsonArray)
        {
            int PreQuestIndex = PreJsonValue->AsNumber();
            Quest_Kill->PreRequisiteQuests.Add(PreQuestIndex);
        }
    }
}