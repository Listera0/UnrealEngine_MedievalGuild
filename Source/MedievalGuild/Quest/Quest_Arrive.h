// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"

#include "Quest_Arrive.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuest_Arrive : public UQuest_Base
{
	GENERATED_BODY()
public:
	virtual bool CheckQuest(int index = 0) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	float AcceptableRadius = 100.0f;

private:
	APlayerController* PlayerController = nullptr;
};
