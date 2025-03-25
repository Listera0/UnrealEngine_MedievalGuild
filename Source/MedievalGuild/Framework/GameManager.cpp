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

}

void AGameManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UQuestManager::GetInstance()->SaveAllQuestDataToJson();

	Super::EndPlay(EndPlayReason);
}
