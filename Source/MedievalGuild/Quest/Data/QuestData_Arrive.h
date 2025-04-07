// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData_Base.h"
#include "QuestData_Arrive.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestData_Arrive : public UQuestData_Base
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Arrive")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Arrive")
	float CapsuleRadius = 100.0f;
	
};
