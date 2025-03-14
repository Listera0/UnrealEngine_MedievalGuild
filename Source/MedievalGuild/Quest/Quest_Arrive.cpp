// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"

void UQuest_Arrive::SetQuestData(UQuestData_Base* InQuest)
{
    Quest = InQuest;
	Quest_Arrive = static_cast<UQuestData_Arrive*>(InQuest);
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
		float Distance = FVector::Dist(PlayerLocation, Quest_Arrive->TargetLocation);

		if (Distance <= Quest_Arrive->AcceptableRadius)
		{
			CompleteQuest();
			return true;
		}
	}

	return false;
}

void UQuest_Arrive::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    JsonObject->SetStringField("QuestName", Quest_Arrive->QuestName);
    JsonObject->SetStringField("Description", Quest_Arrive->Description);
    JsonObject->SetNumberField("QuestIndex", Quest_Arrive->QuestIndex);
    JsonObject->SetNumberField("QuestStatus", static_cast<int32>(Quest_Arrive->QuestStatus));
    JsonObject->SetNumberField("QuestType", static_cast<int32>(Quest_Arrive->QuestType));
    JsonObject->SetNumberField("RewardGold", Quest_Arrive->RewardGold);
    JsonObject->SetNumberField("TargetLocation_X", Quest_Arrive->TargetLocation.X);
    JsonObject->SetNumberField("TargetLocation_Y", Quest_Arrive->TargetLocation.Y);
    JsonObject->SetNumberField("TargetLocation_Z", Quest_Arrive->TargetLocation.Z);
    JsonObject->SetNumberField("AcceptableRadius", Quest_Arrive->AcceptableRadius);

    TArray<TSharedPtr<FJsonValue>> RewardItemJsonArray;
    for (UItemData* PreQuest : Quest_Arrive->RewardItems)
    {
        RewardItemJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest->index));
    }
    JsonObject->SetArrayField("RewardItems", RewardItemJsonArray);


    TArray<TSharedPtr<FJsonValue>> RewardItemAmountJsonArray;
    for (int PreAmount : Quest_Arrive->RewardItemAmount)
    {
        RewardItemAmountJsonArray.Add(MakeShared<FJsonValueNumber>(PreAmount));
    }
    JsonObject->SetArrayField("RewardItemAmount", RewardItemAmountJsonArray);

    TArray<TSharedPtr<FJsonValue>> PreRequisiteJsonArray;
    for (int PreQuest : Quest_Arrive->PreRequisiteQuests)
    {
        PreRequisiteJsonArray.Add(MakeShared<FJsonValueNumber>(PreQuest));
    }
    JsonObject->SetArrayField("PreRequisiteQuests", PreRequisiteJsonArray);
}

void UQuest_Arrive::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
        if (!Quest_Arrive)
            Quest_Arrive = NewObject<UQuestData_Arrive>();

        Quest_Arrive->QuestName = JsonObject->GetStringField("QuestName");
        Quest_Arrive->Description = JsonObject->GetStringField("Description");
        Quest_Arrive->QuestIndex = JsonObject->GetIntegerField("QuestIndex");
        Quest_Arrive->QuestStatus = static_cast<EQuestStatus>(JsonObject->GetIntegerField("QuestStatus"));
        Quest_Arrive->QuestType = static_cast<EQuestType>(JsonObject->GetIntegerField("QuestType"));
        Quest_Arrive->RewardGold = JsonObject->GetIntegerField("RewardGold");
        Quest_Arrive->TargetLocation.X = JsonObject->GetNumberField("TargetLocation_X");
        Quest_Arrive->TargetLocation.Y = JsonObject->GetNumberField("TargetLocation_Y");
        Quest_Arrive->TargetLocation.Z = JsonObject->GetNumberField("TargetLocation_Z");
        Quest_Arrive->AcceptableRadius = JsonObject->GetNumberField("AcceptableRadius");

        const TArray<TSharedPtr<FJsonValue>>& RewardItemAmountJsonArray = JsonObject->GetArrayField("RewardItemAmount");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemAmountJsonArray)
        {
            int RewardItemAmount = PreJsonValue->AsNumber();
            Quest_Arrive->RewardItemAmount.Add(RewardItemAmount);
        }

        const TArray<TSharedPtr<FJsonValue>>& RewardItemJsonArray = JsonObject->GetArrayField("RewardItems");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : RewardItemJsonArray)
        {
            int RewardItemIndex = PreJsonValue->AsNumber();
            UItemData* PreQuest = UItemDataManager::GetInstance()->FindItemData(RewardItemIndex);
            if (PreQuest)
                Quest_Arrive->RewardItems.Add(PreQuest);
        }

        const TArray<TSharedPtr<FJsonValue>>& PreRequisiteJsonArray = JsonObject->GetArrayField("PreRequisiteQuests");
        for (const TSharedPtr<FJsonValue>& PreJsonValue : PreRequisiteJsonArray)
        {
            int PreQuestIndex = PreJsonValue->AsNumber();
            Quest_Arrive->PreRequisiteQuests.Add(PreQuestIndex);
        }
    }
}
