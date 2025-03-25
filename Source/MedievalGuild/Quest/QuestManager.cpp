// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

#include "Quest_Arrive.h"
#include "Quest_Item.h"
#include "Quest_Kill.h"

UQuestManager* UQuestManager::Instance = nullptr;

UQuestManager* UQuestManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UQuestManager>();
        Instance->AddToRoot();
		Instance->LoadAllQuestDataFromJson();
    }
    return Instance;;
}

bool UQuestManager::AddQuestData(UQuestData_Base* QuestData)
{
	bool IsInput = true;
    if (QuestData)
    {
		for (UQuest_Base* Quest : QuestList)
		{
			if (Quest->GetQuestIndex() == QuestData->QuestIndex)
			{
				IsInput = false;
				break;
			}
		}
		if (IsInput)
		{
			UQuest_Base* NewQuest = NewObject<UQuest_Base>();
			if (QuestData->QuestType == EQuestType::Arrive)
			{
				NewQuest = NewObject<UQuest_Arrive>();
			}
			else if (QuestData->QuestType == EQuestType::Item)
			{
				NewQuest = NewObject<UQuest_Item>();
			}
			else if (QuestData->QuestType == EQuestType::KillCount)
			{
				NewQuest = NewObject<UQuest_Kill>();
			}
			NewQuest->SetQuestData(QuestData);
			QuestList.Add(NewQuest);
		}
    }
	else
	{
		IsInput = false;
	}
	return IsInput;
}

void UQuestManager::SaveAllQuestDataToJson()
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	for (UQuest_Base* Quest : QuestList)
	{
		TSharedPtr<FJsonObject> QuestJson = MakeShared<FJsonObject>();

		Quest->SaveFromJson(QuestJson);

		JsonArray.Add(MakeShared<FJsonValueObject>(QuestJson));
	}

	TSharedPtr<FJsonObject> RootJsonObject = MakeShared<FJsonObject>();
	RootJsonObject->SetArrayField("Quests", JsonArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(RootJsonObject.ToSharedRef(), JsonWriter);

	if (FFileHelper::SaveStringToFile(OutputString, *CurrentFilePath, FFileHelper::EEncodingOptions::ForceUTF8))
	{
		UE_LOG(LogTemp, Log, TEXT("Quest data saved successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save quest data"));
	}
}



void UQuestManager::LoadAllQuestDataFromJson()
{
	FString InputString;
	if (FFileHelper::LoadFileToString(InputString, *CurrentFilePath))
	{
		TSharedPtr<FJsonObject> RootJsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(InputString);

		if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
		{
			const TArray<TSharedPtr<FJsonValue>>& JsonArray = RootJsonObject->GetArrayField("Quests");

			QuestList.Empty();

			for (const TSharedPtr<FJsonValue>& JsonValue : JsonArray)
			{
				TSharedPtr<FJsonObject> QuestJson = JsonValue->AsObject();

				UQuest_Base* NewQuest = NewObject<UQuest_Base>();

				NewQuest->LoadFromJson(QuestJson);

				QuestList.Add(NewQuest);
			}
		}
	}
}

UQuest_Base* UQuestManager::FindQuest(int QuestIndex)
{
	UQuest_Base* find = nullptr;

	for (UQuest_Base* quest : QuestList)
	{
		if (quest->GetQuestIndex() == QuestIndex)
		{
			find = quest;
			break;
		}
	}

	return find;
}

void UQuestManager::GetPlayerQuset(TArray<UQuest_Base*>& PlayerQuestList)
{
	for (UQuest_Base* quest : QuestList)
	{
		if (quest->GetQuestData()->HasPlayer)
			PlayerQuestList.Add(quest);
	}
}
