// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTimerResetTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UPatrolTimerResetTask::UPatrolTimerResetTask()
{
    NodeName = "PatrolTimerResetTask";
}

EBTNodeResult::Type UPatrolTimerResetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsFloat("PatrolTimer", 0.0f);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
