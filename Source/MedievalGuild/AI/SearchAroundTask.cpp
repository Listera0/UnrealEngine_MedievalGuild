// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchAroundTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

USearchAroundTask::USearchAroundTask()
{
    NodeName = "SearchAroundTask";
}

EBTNodeResult::Type USearchAroundTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        FVector lastLocation = BlackboardComp->GetValueAsVector("LastLocation");
        FNavLocation RandomLocation;
        UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

        if (NavSys && NavSys->GetRandomReachablePointInRadius(lastLocation, 100.0f, RandomLocation))
        {
            BlackboardComp->SetValueAsVector("LastLocation", RandomLocation.Location);
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}