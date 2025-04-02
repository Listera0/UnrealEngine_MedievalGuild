// Quest_Base.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"  
#include "Data/QuestData_Base.h"
#include "Quest_Base.generated.h"

UCLASS(Blueprintable, BlueprintType)  
class MEDIEVALGUILD_API UQuest_Base : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void CheckQuest(int index = 0);

	void CompleteQuest();

	bool CanStartQuest();
	virtual void StartQuest(UWorld* World);
	void CancleQuest();
	void QuestReward();
	virtual void SetQuestData(UQuestData_Base* InQuest);
	virtual void ClearQuest();
	virtual	void SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject);
	virtual	void LoadFromJson( TSharedPtr<FJsonObject>& JsonObject);
	EQuestStatus GetQuestStatus();
	int GetQuestIndex();
	inline UQuestData_Base* GetQuestData()const { return Quest; };
	inline void PlayerGetQuest() { Quest->HasPlayer = true; };
	inline bool IsPlayerGet()const { return Quest->HasPlayer; };
protected:
	UQuestData_Base* Quest = nullptr;
};
