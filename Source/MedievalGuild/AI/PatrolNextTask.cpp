// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolNextTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/Enemy_1.h"
#include "AIController.h"

UPatrolNextTask::UPatrolNextTask()
{
    NodeName = "PatrolNextTask";
}

EBTNodeResult::Type UPatrolNextTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    AEnemy_1* EnemyActor = Cast<AEnemy_1>(OwnerComp.GetAIOwner()->GetPawn());

    if (BlackboardComp && EnemyActor) {
        if (BlackboardComp->GetValueAsFloat("PatrolTimer") > 5.0f) {
            BlackboardComp->SetValueAsVector("OriginLocation", EnemyActor->GetNextPatrolLocation());
            BlackboardComp->SetValueAsFloat("PatrolTimer", 0.0f);
        }
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}