// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStateTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemyStateTask::UEnemyStateTask()
{
	NodeName = "CheckPatrolTimer";
}

EBTNodeResult::Type UEnemyStateTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (BlackboardComp)
    {
        float timer = BlackboardComp->GetValueAsFloat("PatrolTimer");
        if (timer >= 5.0f) {
            //BlackboardComp->setvalueas
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
    //return EBTNodeResult::InProgress;
}

void UEnemyStateTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
