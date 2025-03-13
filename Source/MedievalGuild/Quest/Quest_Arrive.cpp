// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"

void UQuest_Arrive::SetQuestData(UQuestData_Base* InQuest)
{
	Quest = static_cast<UQuestData_Arrive*>(InQuest);
}

bool UQuest_Arrive::CheckQuest(int index)
{
	if (!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	}

	if (PlayerController)
	{
		FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		float Distance = FVector::Dist(PlayerLocation, Quest->TargetLocation);

		if (Distance <= Quest->AcceptableRadius)
		{
			CompleteQuest();
			return true;
		}
	}

	return false;
}

void UQuest_Arrive::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest->QuestName);
    JsonObject->SetStringField("Description", Quest->Description);
    JsonObject->SetNumberField("QuestIndex", Quest->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest->RewardGold);
    JsonObject->SetNumberField("TargetLocation_X", Quest->TargetLocation.X);
    JsonObject->SetNumberField("TargetLocation_Y", Quest->TargetLocation.Y);
    JsonObject->SetNumberField("TargetLocation_Z", Quest->TargetLocation.Z);
    JsonObject->SetNumberField("AcceptableRadius", Quest->AcceptableRadius);

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

void UQuest_Arrive::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest)
            Quest = NewObject<UQuestData_Arrive>();

        Quest->QuestName = JsonObject->GetStringField("QuestName");
        Quest->Description = JsonObject->GetStringField("Description");
        Quest->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest->RewardGold = JsonObject->GetIntegerField("RewardGold");
        Quest->TargetLocation.X = JsonObject->GetNumberField("TargetLocation_X");
        Quest->TargetLocation.Y = JsonObject->GetNumberField("TargetLocation_Y");
        Quest->TargetLocation.Z = JsonObject->GetNumberField("TargetLocation_Z");
        Quest->AcceptableRadius = JsonObject->GetNumberField("AcceptableRadius");

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

EQuestStatus UQuest_Arrive::GetQuestStatus()
{
    return Quest->QuestStatus;
}

int UQuest_Arrive::GetQuestIndex()
{
    return Quest->QuestIndex;
}
