// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchTimerResetTask.h"
#include "BehaviorTree/BlackboardComponent.h"

USearchTimerResetTask::USearchTimerResetTask()
{
	NodeName = "SearchTimerResetTask";
}

EBTNodeResult::Type USearchTimerResetTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsFloat("SearchTimer", 0.0f);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
