// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Kill.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestManager.h"
void UQuest_Kill::StartQuest(UWorld* World)
{
	Super::StartQuest(World);

	UQuestManager::GetInstance()->OnPlayerKill.AddDynamic(this, &UQuest_Kill::CheckQuest);

}

void UQuest_Kill::SetQuestData(UQuestData_Base* InQuest)
{
    Super::SetQuestData(InQuest);
    if (InQuest->IsA(UQuestData_Kill::StaticClass()))
    {
        Quest_Kill = Cast<UQuestData_Kill>(InQuest);
    }
    else
    {
        Quest_Kill = NewObject<UQuestData_Kill>();
        Quest_Kill->SetData(InQuest);
    }

    Quest_Kill->AddToRoot();
}

void UQuest_Kill::CheckQuest(int index)
{
	if (Quest_Kill->ObjectIndex == index)
	{
		Quest_Kill->Amount++;
	}

	if (Quest_Kill->Amount >= Quest_Kill->RequiredAmount)
	{
		CompleteQuest();
	}
}

void UQuest_Kill::ClearQuest()
{
	Super::ClearQuest();
	if (Quest_Kill)
	{
		Quest_Kill->RemoveFromRoot();
		Quest_Kill = nullptr;
	}
}

void UQuest_Kill::CancleQuest()
{
	Super::CancleQuest();
}

void UQuest_Kill::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    Super::SaveFromJson(JsonObject);

    if (Quest_Kill)
    {
        JsonObject->SetNumberField(TEXT("ObjectIndex"), Quest_Kill->ObjectIndex);
        JsonObject->SetNumberField(TEXT("RequiredAmount"), Quest_Kill->RequiredAmount);
        JsonObject->SetNumberField(TEXT("Amount"), Quest_Kill->Amount);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest_Kill is null in SaveFromJson"));
    }
}

void UQuest_Kill::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        Super::LoadFromJson(JsonObject);
        SetQuestData(Quest);

        if (Quest_Kill)
        {
            if (JsonObject->HasField(TEXT("ObjectIndex")))
                Quest_Kill->ObjectIndex = JsonObject->GetIntegerField(TEXT("ObjectIndex"));
            else
                UE_LOG(LogTemp, Warning, TEXT("ObjectIndex field missing in JSON"));

            if (JsonObject->HasField(TEXT("RequiredAmount")))
                Quest_Kill->RequiredAmount = JsonObject->GetIntegerField(TEXT("RequiredAmount"));
            else
                UE_LOG(LogTemp, Warning, TEXT("RequiredAmount field missing in JSON"));

            if (JsonObject->HasField(TEXT("Amount")))
                Quest_Kill->Amount = JsonObject->GetIntegerField(TEXT("Amount"));
            else
                UE_LOG(LogTemp, Warning, TEXT("Amount field missing in JSON"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Quest_Kill is null in LoadFromJson"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid JSON object passed to LoadFromJson"));
    }
}

UQuestData_Base* UQuest_Kill::GetQuestData() const
{
    return Quest_Kill;
}
