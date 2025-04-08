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
	virtual void CheckQuest(int index, bool IsUpate);

	void CompleteQuest();

	bool CanStartQuest();
	virtual void StartQuest(UWorld* World);
	virtual void CancleQuest();
	virtual void SetQuestData(UQuestData_Base* InQuest);
	virtual void ClearQuest();
	virtual	void SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject);
	virtual	void LoadFromJson( TSharedPtr<FJsonObject>& JsonObject);
	virtual UQuestData_Base* GetQuestData()const;

	void QuestReward();
	EQuestStatus GetQuestStatus();
	int GetQuestIndex();
	inline void PlayerGetQuest() { Quest->HasPlayer = true; };
	inline bool IsPlayerGet()const { return Quest->HasPlayer; };
protected:
	UPROPERTY()
	UQuestData_Base* Quest = nullptr;
};
