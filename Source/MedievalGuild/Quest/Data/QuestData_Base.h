// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../EQuest.h"
#include "../../Item/ItemData.h"
#include "QuestData_Base.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestData_Base : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	EQuestStatus QuestStatus = EQuestStatus::NotStarted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	int QuestIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	EQuestType QuestType = EQuestType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<int> PreRequisiteQuests;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	bool HasPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	TArray<UItemData*> RewardItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	TArray<int>RewardItemAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	int RewardGold = 0;
};
