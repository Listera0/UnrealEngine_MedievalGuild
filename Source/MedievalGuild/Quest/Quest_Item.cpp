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
    Super::SaveFromJson(JsonObject);
    JsonObject->SetNumberField("QuestItemIndex", Quest_Item->QuestIndex);
    JsonObject->SetNumberField("QuestItemAmount", Quest_Item->Amount);
    JsonObject->SetNumberField("QuestItemRequiredAmount", Quest_Item->RequiredAmount);

}

void UQuest_Item::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
		Super::LoadFromJson(JsonObject);
		SetQuestData(Quest);

        Quest_Item->Amount = JsonObject->GetIntegerField("QuestItemAmount");
        Quest_Item->RequiredAmount = JsonObject->GetIntegerField("QuestItemRequiredAmount");

        int ItemIndex = JsonObject->GetIntegerField("QuestItemIndex");
        Quest_Item->QuestItem = UItemDataManager::GetInstance()->FindItemData(ItemIndex);

    }
}