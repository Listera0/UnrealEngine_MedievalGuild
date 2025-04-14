// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolTimerResetTask.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPatrolTimerResetTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPatrolTimerResetTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
