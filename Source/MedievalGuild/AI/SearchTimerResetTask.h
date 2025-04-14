// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SearchTimerResetTask.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API USearchTimerResetTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USearchTimerResetTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
