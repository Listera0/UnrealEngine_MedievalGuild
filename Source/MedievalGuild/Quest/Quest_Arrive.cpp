// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestManager.h"
#include "Actor/ArrivalTriggerActor.h"

void UQuest_Arrive::StartQuest(UWorld* World)
{
   Super::StartQuest(World);
   if (World && Quest_Arrive)
   {
       FActorSpawnParameters SpawnParams;
       AArrivalTriggerActor* ArrivalTrigger = World->SpawnActor<AArrivalTriggerActor>(AArrivalTriggerActor::StaticClass(), Quest_Arrive->TargetLocation, FRotator::ZeroRotator, SpawnParams);

       if (ArrivalTrigger)
       {
           ArrivalTrigger->StartQuest(Quest_Arrive->CapsuleRadius, Quest->QuestIndex);
           UQuestManager::GetInstance()->OnPlayerArrived.AddDynamic(this, &UQuest_Arrive::CheckQuest);
       }
   }
}

void UQuest_Arrive::SetQuestData(UQuestData_Base* InQuest)
{
    Super::SetQuestData(InQuest);
    Quest_Arrive = static_cast<UQuestData_Arrive*>(InQuest);
    Quest_Arrive->AddToRoot();
}

void UQuest_Arrive::CheckQuest(int index)
{
   if (Quest->QuestIndex == index)
   {
       CompleteQuest();
       UQuestManager::GetInstance()->OnPlayerArrived.RemoveDynamic(this, &UQuest_Arrive::CheckQuest);
   }
}

void UQuest_Arrive::ClearQuest()
{
   Super::ClearQuest();
   if (Quest_Arrive)
   {
       Quest_Arrive->RemoveFromRoot();
       Quest_Arrive = nullptr;
   }
}

void UQuest_Arrive::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
   Super::SaveFromJson(JsonObject);

   if (Quest_Arrive)
   {
       JsonObject->SetNumberField(TEXT("TargetLocation_X"), Quest_Arrive->TargetLocation.X);
       JsonObject->SetNumberField(TEXT("TargetLocation_Y"), Quest_Arrive->TargetLocation.Y);
       JsonObject->SetNumberField(TEXT("TargetLocation_Z"), Quest_Arrive->TargetLocation.Z);
       JsonObject->SetNumberField(TEXT("CapsuleRadius"), Quest_Arrive->CapsuleRadius);
   }
   else
   {
       UE_LOG(LogTemp, Warning, TEXT("Quest_Arrive is null in SaveFromJson"));
   }
}

void UQuest_Arrive::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
   if (JsonObject.IsValid())
   {
       Super::LoadFromJson(JsonObject);
       SetQuestData(Quest);

       if (Quest_Arrive)
       {
           if (JsonObject->HasField(TEXT("TargetLocation_X")))
               Quest_Arrive->TargetLocation.X = JsonObject->GetNumberField(TEXT("TargetLocation_X"));
           else
               UE_LOG(LogTemp, Warning, TEXT("TargetLocation_X field missing in JSON"));

           if (JsonObject->HasField(TEXT("TargetLocation_Y")))
               Quest_Arrive->TargetLocation.Y = JsonObject->GetNumberField(TEXT("TargetLocation_Y"));
           else
               UE_LOG(LogTemp, Warning, TEXT("TargetLocation_Y field missing in JSON"));

           if (JsonObject->HasField(TEXT("TargetLocation_Z")))
               Quest_Arrive->TargetLocation.Z = JsonObject->GetNumberField(TEXT("TargetLocation_Z"));
           else
               UE_LOG(LogTemp, Warning, TEXT("TargetLocation_Z field missing in JSON"));

           if (JsonObject->HasField(TEXT("CapsuleRadius")))
               Quest_Arrive->CapsuleRadius = JsonObject->GetNumberField(TEXT("CapsuleRadius"));
           else
               UE_LOG(LogTemp, Warning, TEXT("AcceptableRadius field missing in JSON"));
       }
       else
       {
           UE_LOG(LogTemp, Warning, TEXT("Quest_Arrive is null in LoadFromJson"));
       }
   }
   else
   {
       UE_LOG(LogTemp, Error, TEXT("Invalid JSON object passed to LoadFromJson"));
   }
}
