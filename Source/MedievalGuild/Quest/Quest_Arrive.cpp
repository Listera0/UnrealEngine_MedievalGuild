#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestManager.h"
#include "Actor/ArrivalTriggerActor.h"

void UQuest_Arrive::StartQuest(UWorld* World)
{
    Super::StartQuest(World);

    if (!World || !Quest_Arrive)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid parameters in StartQuest. World or Quest_Arrive is null."));
        return;
    }

    FActorSpawnParameters SpawnParams;
    AArrivalTriggerActor* ArrivalTrigger = World->SpawnActor<AArrivalTriggerActor>(AArrivalTriggerActor::StaticClass(), Quest_Arrive->TargetLocation, FRotator::ZeroRotator, SpawnParams);


    if (ArrivalTrigger)
    {
        ArrivalTrigger->StartQuest(Quest_Arrive->CapsuleRadius, Quest_Arrive->QuestIndex);
        UQuestManager::GetInstance()->OnPlayerArrived.AddDynamic(this, &UQuest_Arrive::CheckQuest);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn ArrivalTriggerActor."));
    }

}

void UQuest_Arrive::SetQuestData(UQuestData_Base* InQuest)
{
    Super::SetQuestData(InQuest);
    if (InQuest->IsA(UQuestData_Arrive::StaticClass()))
    {
        Quest_Arrive = Cast<UQuestData_Arrive>(InQuest);
    }
    else
    {
        Quest_Arrive = NewObject<UQuestData_Arrive>();
        Quest_Arrive->SetData(InQuest);
    }

    Quest_Arrive->AddToRoot();
}

void UQuest_Arrive::CheckQuest(int index, bool isUpdate)
{
    if (Quest_Arrive && Quest_Arrive->QuestIndex == index)
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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest_Arrive is already null in ClearQuest."));
    }
}

void UQuest_Arrive::CancleQuest()
{
	Super::CancleQuest();
    UQuestManager::GetInstance()->OnPlayerArrived.RemoveDynamic(this, &UQuest_Arrive::CheckQuest);
}

void UQuest_Arrive::SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject)
{
    Super::SaveFromJson(JsonObject);

    if (!Quest_Arrive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest_Arrive is null in SaveFromJson. Skipping save."));
        return;
    }

    JsonObject->SetNumberField(TEXT("TargetLocation_X"), Quest_Arrive->TargetLocation.X);
    JsonObject->SetNumberField(TEXT("TargetLocation_Y"), Quest_Arrive->TargetLocation.Y);
    JsonObject->SetNumberField(TEXT("TargetLocation_Z"), Quest_Arrive->TargetLocation.Z);
    JsonObject->SetNumberField(TEXT("CapsuleRadius"), Quest_Arrive->CapsuleRadius);
}

void UQuest_Arrive::LoadFromJson(TSharedPtr<FJsonObject>& JsonObject)
{
    if (!JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid JSON object passed to LoadFromJson."));
        return;
    }

    Super::LoadFromJson(JsonObject);
    SetQuestData(Quest);

    if (!Quest_Arrive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest_Arrive is null in LoadFromJson."));
        return;
    }


    Quest_Arrive->TargetLocation.X = JsonObject->HasField(TEXT("TargetLocation_X")) ? JsonObject->GetNumberField(TEXT("TargetLocation_X")) : 0;
    Quest_Arrive->TargetLocation.Y = JsonObject->HasField(TEXT("TargetLocation_Y")) ? JsonObject->GetNumberField(TEXT("TargetLocation_Y")) : 0;
    Quest_Arrive->TargetLocation.Z = JsonObject->HasField(TEXT("TargetLocation_Z")) ? JsonObject->GetNumberField(TEXT("TargetLocation_Z")) : 0;
    Quest_Arrive->CapsuleRadius = JsonObject->HasField(TEXT("CapsuleRadius")) ? JsonObject->GetNumberField(TEXT("CapsuleRadius")) : 0;

    if (!JsonObject->HasField(TEXT("TargetLocation_X"))) UE_LOG(LogTemp, Warning, TEXT("TargetLocation_X field missing in JSON."));
    if (!JsonObject->HasField(TEXT("TargetLocation_Y"))) UE_LOG(LogTemp, Warning, TEXT("TargetLocation_Y field missing in JSON."));
    if (!JsonObject->HasField(TEXT("TargetLocation_Z"))) UE_LOG(LogTemp, Warning, TEXT("TargetLocation_Z field missing in JSON."));
    if (!JsonObject->HasField(TEXT("CapsuleRadius"))) UE_LOG(LogTemp, Warning, TEXT("CapsuleRadius field missing in JSON."));
}

UQuestData_Base* UQuest_Arrive::GetQuestData() const
{
    return Quest_Arrive;
}
