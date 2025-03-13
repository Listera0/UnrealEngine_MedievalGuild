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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	UItemData* QuestItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int Amount = 0;
};
