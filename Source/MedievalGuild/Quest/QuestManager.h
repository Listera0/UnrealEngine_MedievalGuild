// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest_Base.h"
#include "QuestManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UQuestManager : public UObject
{
	GENERATED_BODY()
	
public:
	UQuestManager();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	static UQuestManager* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	bool AddQuestData(UQuestData_Base* QuestData);

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void SaveAllQuestDataToJson();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	void LoadAllQuestDataFromJson();

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	TArray<UQuest_Base*> GetQuestDataList() const { return QuestList; }

	UFUNCTION(BlueprintCallable, Category = "Quest Data Manager")
	UQuest_Base* FindQuest(int QuestIndex);
	/*
	해야할것 
	questData 만들어서 quest가 가지게 하기( 함수랑 데이터 분리목적)
	https://programmingdev.com/%EC%96%B8%EB%A6%AC%EC%96%BC-%EC%97%94%EC%A7%84%EC%97%90%EC%84%9C-%ED%99%95%EC%9E%A5-%EA%B0%80%EB%8A%A5%ED%95%9C-%EC%97%85%EC%A0%81-%EB%B0%8F-%ED%80%98%EC%8A%A4%ED%8A%B8-%EC%8B%9C%EC%8A%A4%ED%85%9C/
	https://velog.io/@nyong_u_u/DAY-36-37-%ED%80%98%EC%8A%A4%ED%8A%B8-%EC%8B%9C%EC%8A%A4%ED%85%9C-%EA%B0%9C%ED%8E%B8

	*/

private:
	UPROPERTY()
	TArray<UQuest_Base*> QuestList;

	static UQuestManager* Instance;

	FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Quest/Data/TestQuest.json");
};
