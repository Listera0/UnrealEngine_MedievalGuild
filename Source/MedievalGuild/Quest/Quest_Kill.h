// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"
#include "Quest_Kill.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuest_Kill : public UQuest_Base
{
	GENERATED_BODY()
	
public:
	virtual bool CheckQuest(int index = 0) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int ObjectIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int Amount = 0;
};
