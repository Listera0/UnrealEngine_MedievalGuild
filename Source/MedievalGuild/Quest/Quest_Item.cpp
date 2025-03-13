#include "Quest_Item.h"
#include "../Item/ItemDataManager.h"

void UQuest_Item::SetQuestData(UQuestData_Base* InQuest)
{
	Quest = static_cast<UQuestData_Item*>(InQuest);
}

bool UQuest_Item::CheckQuest(int ItemID)
{
	if (!Quest->QuestItem) return false;

	if (Quest->QuestItem->index == ItemID)
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

void UQuest_Item::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest->QuestName);
    JsonObject->SetStringField("Description", Quest->Description);
    JsonObject->SetNumberField("QuestIndex", Quest->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest->RewardGold);

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

void UQuest_Item::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest)
            Quest = NewObject<UQuestData_Item>();

        Quest->QuestName = JsonObject->GetStringField("QuestName");
        Quest->Description = JsonObject->GetStringField("Description");
        Quest->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest->RewardGold = JsonObject->GetIntegerField("RewardGold");

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

EQuestStatus UQuest_Item::GetQuestStatus()
{
    return Quest->QuestStatus;
}

int UQuest_Item::GetQuestIndex()
{
    return Quest->QuestIndex;
}
