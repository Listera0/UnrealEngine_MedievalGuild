// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"

#include "Quest_Item.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuest_Item : public UQuest_Base
{
	GENERATED_BODY()
	
public:
	virtual bool CheckQuest(int index = 0) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TSubclassOf<AItem_Base> QuestItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int Amount = 0;
};
