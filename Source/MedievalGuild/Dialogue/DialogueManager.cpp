// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "../Quest/QuestManager.h"
#include "../Quest/Quest_Base.h"
UDialogueManager* UDialogueManager::Instance = nullptr;

UDialogueManager* UDialogueManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UDialogueManager>();
		Instance->AddToRoot();
		Instance->LoadAllDialogueFromJson(TEXT("DialogueData.json"));
	}
	return Instance;
}

void UDialogueManager::ClearUp()
{
	if (Instance)
	{
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}

void UDialogueManager::AddDialogue(UDialogue* Dialogue)
{
	if (Dialogue)
	{
		bool IsValid = false;
		for (UDialogue* ListDialogue : DialogueList)
		{
			if (ListDialogue->DialogueIndex == Dialogue->DialogueIndex)
			{
				IsValid = true;
				break;
			}
		}
		if (!IsValid)
		{
			DialogueList.Add(Dialogue);
		}
	}
}

void UDialogueManager::SaveAllDialogueToJson()
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;

	for (UDialogue* DialogueData : DialogueList)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		JsonObject->SetNumberField(TEXT("DialogueIndex"), DialogueData->DialogueIndex);
		JsonObject->SetStringField(TEXT("DialogueText"), DialogueData->DialogueText);
		JsonObject->SetBoolField(TEXT("bIsEndOfDialogue"), DialogueData->bIsEndOfDialogue);
		JsonObject->SetBoolField(TEXT("bIsDialogueOption"), DialogueData->bIsDialogueOption);
		JsonObject->SetNumberField(TEXT("NextDialogueIndex"), DialogueData->NextDialogueIndex);

		if (DialogueData->bIsDialogueOption)
		{
			TArray<TSharedPtr<FJsonValue>> DialogueOptionsArray;
			for (const FDialogueOption& Option : DialogueData->DialogueOptions)
			{
				TSharedPtr<FJsonObject> OptionObject = MakeShareable(new FJsonObject());
				OptionObject->SetStringField(TEXT("OptionText"), Option.OptionText);
				OptionObject->SetNumberField(TEXT("NextDialogueID"), Option.NextDialogueID);
				OptionObject->SetBoolField(TEXT("bGiveQuest"), Option.bGiveQuest);
				OptionObject->SetNumberField(TEXT("QuestIndex"), Option.QuestIndex);
				DialogueOptionsArray.Add(MakeShareable(new FJsonValueObject(OptionObject)));
			}
			JsonObject->SetArrayField(TEXT("DialogueOptions"), DialogueOptionsArray);
		}

		TArray<TSharedPtr<FJsonValue>> CompleteQuestIndexArray;
		for (int Index : DialogueData->CompleteQuestIndex)
		{
			CompleteQuestIndexArray.Add(MakeShareable(new FJsonValueNumber(Index)));
		}
		JsonObject->SetArrayField(TEXT("CompleteQuestIndex"), CompleteQuestIndexArray);

		TArray<TSharedPtr<FJsonValue>> ResponsesArray;
		for (const FString& Response : DialogueData->Responses)
		{
			ResponsesArray.Add(MakeShareable(new FJsonValueString(Response)));
		}
		JsonObject->SetArrayField(TEXT("Responses"), ResponsesArray);

		JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
	}
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	if (FJsonSerializer::Serialize(JsonArray, Writer))
	{
		FString Path = CurrentFilePath + TEXT("DialogueData.json");
		FFileHelper::SaveStringToFile(OutputString, *Path, FFileHelper::EEncodingOptions::ForceUTF8);
	}

}

void UDialogueManager::LoadAllDialogueFromJson(const FString& FilePath)
{
	FString FileContents;
	FString Path = CurrentFilePath + FilePath;
	if (FFileHelper::LoadFileToString(FileContents, *Path))
	{
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			DialogueList.Empty();
			for (TSharedPtr<FJsonValue> JsonValue : JsonArray)
			{
				if (JsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
					UDialogue* LoadedDialogue = NewObject<UDialogue>();
					LoadedDialogue->DialogueIndex = JsonObject->GetNumberField(TEXT("DialogueIndex"));
					LoadedDialogue->DialogueText = JsonObject->GetStringField(TEXT("DialogueText"));
					LoadedDialogue->bIsEndOfDialogue = JsonObject->GetBoolField(TEXT("bIsEndOfDialogue"));
					LoadedDialogue->bIsDialogueOption = JsonObject->GetBoolField(TEXT("bIsDialogueOption"));
					LoadedDialogue->NextDialogueIndex = JsonObject->GetNumberField(TEXT("NextDialogueIndex"));

					if (LoadedDialogue->bIsDialogueOption)
					{
						const TArray<TSharedPtr<FJsonValue>>& DialogueOptionsArray = JsonObject->GetArrayField(TEXT("DialogueOptions"));
						for (const TSharedPtr<FJsonValue>& Value : DialogueOptionsArray)
						{
							if (Value->Type == EJson::Object)
							{
								TSharedPtr<FJsonObject> OptionObject = Value->AsObject();
								FDialogueOption Option;
								Option.OptionText = OptionObject->GetStringField(TEXT("OptionText"));
								Option.NextDialogueID = OptionObject->GetNumberField(TEXT("NextDialogueID"));
								Option.bGiveQuest = OptionObject->GetBoolField(TEXT("bGiveQuest"));
								Option.QuestIndex = OptionObject->GetNumberField(TEXT("QuestIndex"));
								LoadedDialogue->DialogueOptions.Add(Option);
							}
						}
					}

					const TArray<TSharedPtr<FJsonValue>>& CompleteQuestIndexArray = JsonObject->GetArrayField(TEXT("CompleteQuestIndex"));
					for (const TSharedPtr<FJsonValue>& Value : CompleteQuestIndexArray)
					{
						LoadedDialogue->CompleteQuestIndex.Add(Value->AsNumber());
					}
					const TArray<TSharedPtr<FJsonValue>>& ResponsesArray = JsonObject->GetArrayField(TEXT("Responses"));
					for (const TSharedPtr<FJsonValue>& Value : ResponsesArray)
					{
						LoadedDialogue->Responses.Add(Value->AsString());
					}
					DialogueList.Add(LoadedDialogue);
				}
			}
		}
	}
}

UDialogue* const  UDialogueManager::FindDialogue(int DialogueIndex)
{
	for (UDialogue* Dialogue : DialogueList)
	{
		if (Dialogue->DialogueIndex == DialogueIndex)
		{
			return Dialogue;
		}
	}
	return nullptr;
}

bool UDialogueManager::IsDialogueOn(UDialogue* dialogue)
{
	bool IsOn = false;
	if (dialogue)
	{
		for (int index : dialogue->CompleteQuestIndex)
		{
			UQuest_Base* Quest = UQuestManager::GetInstance()->FindQuest(index);
			if (Quest->GetQuestStatus() == EQuestStatus::Completed)
			{
				IsOn = true;
			}
			else
			{
				IsOn = false;
				break;
			}
		}
	}
	return IsOn;
}
