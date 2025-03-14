#include "Quest_Item.h"
#include "../Item/ItemDataManager.h"

void UQuest_Item::SetQuestData(UQuestData_Base* InQuest)
{
    Quest = InQuest;
	Quest_Item = static_cast<UQuestData_Item*>(InQuest);
}

bool UQuest_Item::CheckQuest(int ItemID)
{
	if (!Quest_Item->QuestItem) return false;

	if (Quest_Item->QuestItem->index == ItemID)
	{
		Quest_Item->Amount++;
	}

	if (Quest_Item->Amount >= Quest_Item->RequiredAmount)
	{
		CompleteQuest();
		return true;
	}

	return false;
}

void UQuest_Item::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest_Item->QuestName);
    JsonObject->SetStringField("Description", Quest_Item->Description);
    JsonObject->SetNumberField("QuestIndex", Quest_Item->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest_Item->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest_Item->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest_Item->RewardGold);

    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest_Item->RewardItems)
    {
        RewardItemJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest->index));
    }
    JsonObject->SetArrayField("RewardItems", RewardItemJsonArray);


    TArray<TSharedPtr<FJsonValue>> RewardItemAmountJsonArray;
    for (int PreAmount : Quest_Item->RewardItemAmount)
    {
        RewardItemAmountJsonArray.Add(MakeShared<FJsonValueNumber>(PreAmount));
    }
    JsonObject->SetArrayField("RewardItemAmount", RewardItemAmountJsonArray);

    TArray<TSharedPtr<FJsonValue>> PreRequisiteJsonArray;
    for (int PreQuest : Quest_Item->PreRequisiteQuests)
    {
        PreRequisiteJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest));
    }
    JsonObject->SetArrayField("PreRequisiteQuests", PreRequisiteJsonArray);
}

void UQuest_Item::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest_Item)
            Quest_Item = NewObject<UQuestData_Item>();

        Quest_Item->QuestName = JsonObject->GetStringField("QuestName");
        Quest_Item->Description = JsonObject->GetStringField("Description");
        Quest_Item->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest_Item->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest_Item->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest_Item->RewardGold = JsonObject->GetIntegerField("RewardGold");

        const TArray<TSharedPtr<FJsonValue>>& RewardItemAmountJsonArray = JsonObject->GetArrayField("RewardItemAmount");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemAmountJsonArray)
        {
            int RewardItemAmount = PreJsonValue->AsNumber();
            Quest_Item->RewardItemAmount.Add(RewardItemAmount);
        }

        const TArray<TSharedPtr<FJsonValue>>& RewardItemJsonArray = JsonObject->GetArrayField("RewardItems");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemJsonArray)
        {
            int RewardItemIndex = PreJsonValue->AsNumber();
            UItemData* PreQuest = UItemDataManager::GetInstance()->FindItemData(RewardItemIndex);
            if (PreQuest)
                Quest_Item->RewardItems.Add(PreQuest);
        }

        const TArray<TSharedPtr<FJsonValue>>& PreRequisiteJsonArray = JsonObject->GetArrayField("PreRequisiteQuests");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : PreRequisiteJsonArray)
        {
            int PreQuestIndex = PreJsonValue->AsNumber();
            Quest_Item->PreRequisiteQuests.Add(PreQuestIndex);
        }
    }
}