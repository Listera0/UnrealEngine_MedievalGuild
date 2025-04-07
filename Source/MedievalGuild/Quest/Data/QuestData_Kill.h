// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData_Base.h"
#include "QuestData_Kill.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestData_Kill : public UQuestData_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Kill")
	int ObjectIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Kill")
	int RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Kill")
	int Amount = 0;
	
};
