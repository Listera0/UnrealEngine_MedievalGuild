// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"
#include "Data/QuestData_Arrive.h"
#include "Quest_Arrive.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuest_Arrive : public UQuest_Base
{
	GENERATED_BODY()
public:
	virtual void StartQuest(UWorld* World) override;
	virtual void SetQuestData(UQuestData_Base* InQuest) override;
	virtual void CheckQuest(int index = 0) override;
	virtual void ClearQuest() override;
	virtual	void SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject) override;
	virtual	void LoadFromJson(TSharedPtr<FJsonObject>& JsonObject) override;
private:
	UQuestData_Arrive* Quest_Arrive;
	APlayerController* PlayerController = nullptr;

};
