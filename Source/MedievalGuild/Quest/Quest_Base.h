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
	bool CanStartQuest();
	void StartQuest();
	void CancleQuest();
	void CompleteQuest();
	void QuestReward();
	virtual void SetQuestData(UQuestData_Base* InQuest);
	virtual bool CheckQuest(int index = 0);
	virtual	void SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject);
	virtual	void LoadFromJson( TSharedPtr<FJsonObject>& JsonObject);
	virtual EQuestStatus GetQuestStatus();
	virtual int GetQuestIndex();
private:
	UQuestData_Base* Quest;
};
