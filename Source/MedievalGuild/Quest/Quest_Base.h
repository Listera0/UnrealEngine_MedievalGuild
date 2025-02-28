// Quest_Base.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"  
#include "EQuest.h"
#include "../Item/Item_Base.h"
#include "Quest_Base.generated.h"

UCLASS(Blueprintable, BlueprintType)  
class MEDIEVALGUILD_API UQuest_Base : public UDataAsset 
{
	GENERATED_BODY()

public:
	bool CanStartQuest();
	void StartQuest();
	void CancleQuest();
	void CompleteQuest();
	void QuestReward();
	virtual bool CheckQuest(int index = 0);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	EQuestStatus QuestStatus = EQuestStatus::NotStarted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	EQuestType QuestType = EQuestType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FName QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FString Description;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<UQuest_Base*> PreRequisiteQuests;  


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	TSubclassOf<AItem_Base> RewardItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	int RewardItemAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Reward")
	int RewardGold;
};
