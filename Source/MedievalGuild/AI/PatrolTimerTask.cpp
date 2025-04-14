// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTimerTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UPatrolTimerTask::UPatrolTimerTask()
{
	NodeName = "PatrolTimerTask";
}

EBTNodeResult::Type UPatrolTimerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsFloat("PatrolTimer", BlackboardComp->GetValueAsFloat("PatrolTimer") + 0.1f);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
