// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"
#include "Data/QuestData_Kill.h"
#include "Quest_Kill.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuest_Kill : public UQuest_Base
{
	GENERATED_BODY()
	
public:
	virtual void StartQuest(UWorld* World) override;
	virtual void SetQuestData(UQuestData_Base* InQuest) override;
	virtual void CheckQuest(int index) override;
	virtual void ClearQuest() override;
	virtual void CancleQuest() override;
	virtual	void SaveFromJson(const TSharedPtr<FJsonObject>& JsonObject) override;
	virtual	void LoadFromJson(TSharedPtr<FJsonObject>& JsonObject) override;
	virtual UQuestData_Base* GetQuestData()const override;

private:
	UPROPERTY()
	UQuestData_Kill* Quest_Kill;
};
