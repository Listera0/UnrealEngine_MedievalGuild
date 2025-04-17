// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest_Base.h"
#include "QuestManager.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdatePlayerQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerArrived, int, QuestIndex, bool, IsUpate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerKill, int, AcotrIndex, bool, IsUpate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerAddItem, int, ItemIndex, bool, IsUpate);
UCLASS()
class MEDIEVALGUILD_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	static UQuestManager* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void CleanUp();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	bool AddQuestData(UQuestData_Base* QuestData);

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void SaveAllQuestDataToJson();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void LoadAllQuestDataFromJson();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	TArray<UQuest_Base*> GetQuestDataList() const { return QuestList; }

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	UQuest_Base* FindQuest(int Quest);

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void GetPlayerQuset(TArray<UQuest_Base*>& PlayerQuestList);

public:
	UPROPERTY(BlueprintAssignable, Category = "Quest Data Manager")
	FOnPlayerArrived OnPlayerArrived;

	UPROPERTY(BlueprintAssignable, Category = "Quest Data Manager")
	FOnPlayerKill OnPlayerKill;

	UPROPERTY(BlueprintAssignable, Category = "Quest Data Manager")
	FOnPlayerAddItem OnPlayerAddItem;

	UPROPERTY(BlueprintAssignable, Category = "Quest Data Manager")
	FUpdatePlayerQuest OnUpdatePlayerQuest;
private:
	UPROPERTY()
	TArray<UQuest_Base*> QuestList;

	static UQuestManager* Instance;

	FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Quest/Data/TestQuest.json");
};
