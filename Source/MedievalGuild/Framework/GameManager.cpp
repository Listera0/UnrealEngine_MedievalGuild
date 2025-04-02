// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "../Quest/QuestManager.h"

AGameManager::AGameManager()
{
	Blueprints = CreateDefaultSubobject<UBlueprintBindComponent>(FName("BlueprintBind"));
}

void AGameManager::StartPlay()
{
	Super::StartPlay();
	ItemDataManager = UItemDataManager::GetInstance();	
	QuestDataManager = UQuestManager::GetInstance();
}

void AGameManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ItemDataManager)
		ItemDataManager->ClearUp();
	if (QuestDataManager)
		QuestDataManager->CleanUp();
	
	Super::EndPlay(EndPlayReason);
}

void AGameManager::GameEndSequence()
{

	if (ItemDataManager)
		ItemDataManager->ClearUp();
	if (QuestDataManager)
	{
		QuestDataManager->SaveAllQuestDataToJson();
		QuestDataManager->CleanUp();
	}
}
