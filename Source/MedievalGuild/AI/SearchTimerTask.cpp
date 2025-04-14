// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchTimerTask.h"
#include "BehaviorTree/BlackboardComponent.h"

USearchTimerTask::USearchTimerTask()
{
    NodeName = "SearchTimerTask";
}

EBTNodeResult::Type USearchTimerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        BlackboardComp->SetValueAsFloat("SearchTimer", BlackboardComp->GetValueAsFloat("SearchTimer") + 0.1f);
        BlackboardComp->SetValueAsFloat("TotalTimer", BlackboardComp->GetValueAsFloat("TotalTimer") + 0.1f);

        if (BlackboardComp->GetValueAsFloat("TotalTimer") > 10.0f) {
            BlackboardComp->SetValueAsEnum("State", 0);
            BlackboardComp->SetValueAsFloat("TotalTimer", 0.0f);
            return EBTNodeResult::Failed;
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
