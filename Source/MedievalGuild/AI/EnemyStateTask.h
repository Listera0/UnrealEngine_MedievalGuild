// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyStateTask.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UEnemyStateTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyStateTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
