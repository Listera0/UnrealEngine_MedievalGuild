// Fill out your copyright notice in the Description page of Project Settings.


#include "RecordLastLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

URecordLastLocation::URecordLastLocation()
{
    NodeName = "RecordLastLocation";
}

EBTNodeResult::Type URecordLastLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        AActor* targetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
        if(!targetActor) return EBTNodeResult::Failed;

        BlackboardComp->SetValueAsVector("LastLocation", targetActor->GetActorLocation());
        BlackboardComp->SetValueAsEnum("State", 1);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}