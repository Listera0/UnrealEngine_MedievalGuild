// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RecordLastLocation.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API URecordLastLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	URecordLastLocation();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
