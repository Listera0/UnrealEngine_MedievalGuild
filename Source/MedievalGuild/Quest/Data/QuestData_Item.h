// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData_Base.h"
#include "QuestData_Item.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestData_Item : public UQuestData_Base
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Item")
	int QuestItemIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Item")
	int RequiredAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Item")
	int Amount = 0;
};
