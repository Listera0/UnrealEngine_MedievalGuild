// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestManager.h"
#include "Actor/ArrivalTriggerActor.h"

void UQuest_Arrive::StartQuest(UWorld* World)
{
	Super::StartQuest(World);
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		AArrivalTriggerActor* ArrivalTrigger = World->SpawnActor<AArrivalTriggerActor>(AArrivalTriggerActor::StaticClass(), Quest_Arrive->TargetLocation, FRotator::ZeroRotator, SpawnParams);

		if (ArrivalTrigger)
		{
			ArrivalTrigger->SetRadius(Quest_Arrive->AcceptableRadius);
			ArrivalTrigger->OnPlayerArrived.AddDynamic(this, &UQuest_Arrive::CompleteQuest);
		}
	}
}

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
    Super::SaveFromJson(JsonObject);
    JsonObject->SetNumberField("TargetLocation_X", Quest_Arrive->TargetLocation.X);
    JsonObject->SetNumberField("TargetLocation_Y", Quest_Arrive->TargetLocation.Y);
    JsonObject->SetNumberField("TargetLocation_Z", Quest_Arrive->TargetLocation.Z);
    JsonObject->SetNumberField("AcceptableRadius", Quest_Arrive->AcceptableRadius);

}

void UQuest_Arrive::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (JsonObject.IsValid())
    {
		Super::LoadFromJson(JsonObject);
        SetQuestData(Quest);

        Quest_Arrive->TargetLocation.X = JsonObject->GetNumberField("TargetLocation_X");
        Quest_Arrive->TargetLocation.Y = JsonObject->GetNumberField("TargetLocation_Y");
        Quest_Arrive->TargetLocation.Z = JsonObject->GetNumberField("TargetLocation_Z");
        Quest_Arrive->AcceptableRadius = JsonObject->GetNumberField("AcceptableRadius");
    }
}
