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
    Super::SaveFromJson(JsonObject);
    JsonObject->SetNumberField("ObjectIndex", Quest_Kill->ObjectIndex);
    JsonObject->SetNumberField("RequiredAmount", Quest_Kill->RequiredAmount);
    JsonObject->SetNumberField("Amount", Quest_Kill->Amount);

}

void UQuest_Kill::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
		Super::LoadFromJson(JsonObject);
		SetQuestData(Quest);

        Quest_Kill->ObjectIndex = JsonObject->GetIntegerField("ObjectIndex");
        Quest_Kill->RequiredAmount = JsonObject->GetIntegerField("RequiredAmount");
        Quest_Kill->Amount = JsonObject->GetIntegerField("Amount");
    }
}