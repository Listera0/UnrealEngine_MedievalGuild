// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SearchTimerTask.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API USearchTimerTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USearchTimerTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
