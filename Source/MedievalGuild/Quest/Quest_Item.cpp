#include "Quest_Item.h"
#include "../Item/ItemDataManager.h"

void UQuest_Item::StartQuest(UWorld* World)
{
	Super::StartQuest(World);
}

void UQuest_Item::SetQuestData(UQuestData_Base* InQuest)
{
	Super::SetQuestData(InQuest);
	Quest_Item = NewObject<UQuestData_Item>();
	Quest_Item->SetData(InQuest);

	Quest_Item->AddToRoot();
}

void UQuest_Item::CheckQuest(int ItemID)
{
    if (!Quest_Item->QuestItem)
        return;

	if (Quest_Item->QuestItem->index == ItemID)
	{
		Quest_Item->Amount++;
	}

	if (Quest_Item->Amount >= Quest_Item->RequiredAmount)
	{
		CompleteQuest();
	}

}

void UQuest_Item::ClearQuest()
{
	Super::ClearQuest();
	if (Quest_Item)
	{
		Quest_Item->RemoveFromRoot();
		Quest_Item = nullptr;
	}
}

void UQuest_Item::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    Super::SaveFromJson(JsonObject);

    if (Quest_Item)
    {
        JsonObject->SetNumberField(TEXT("QuestItemIndex"), Quest_Item->QuestIndex);
        JsonObject->SetNumberField(TEXT("QuestItemAmount"), Quest_Item->Amount);
        JsonObject->SetNumberField(TEXT("QuestItemRequiredAmount"), Quest_Item->RequiredAmount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest_Item is null in SaveFromJson"));
    }
}

void UQuest_Item::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        Super::LoadFromJson(JsonObject);
        SetQuestData(Quest);

        if (Quest_Item)
        {
            if (JsonObject->HasField(TEXT("QuestItemAmount")))
                Quest_Item->Amount = JsonObject->GetIntegerField(TEXT("QuestItemAmount"));
            else
                UE_LOG(LogTemp, Warning, TEXT("QuestItemAmount field missing in JSON"));

            if (JsonObject->HasField(TEXT("QuestItemRequiredAmount")))
                Quest_Item->RequiredAmount = JsonObject->GetIntegerField(TEXT("QuestItemRequiredAmount"));
            else
                UE_LOG(LogTemp, Warning, TEXT("QuestItemRequiredAmount field missing in JSON"));

            if (JsonObject->HasField(TEXT("QuestItemIndex")))
            {
                int ItemIndex = JsonObject->GetIntegerField(TEXT("QuestItemIndex"));
                Quest_Item->QuestItem = UItemDataManager::GetInstance()->FindItemData(ItemIndex);

                if (!Quest_Item->QuestItem)
                {
                    UE_LOG(LogTemp, Warning, TEXT("QuestItem not found for index %d"), ItemIndex);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("QuestItemIndex field missing in JSON"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Quest_Item is null in LoadFromJson"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid JSON object passed to LoadFromJson"));
    }
}
