// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolNextTask.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPatrolNextTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPatrolNextTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
