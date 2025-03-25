// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestAddActor.h"

// Sets default values
AQuestAddActor::AQuestAddActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AQuestAddActor::BeginPlay()
{
	Super::BeginPlay();
	
	for (UQuestData_Base* quest : QuestAddList)
	{
		UQuestManager::GetInstance()->AddQuestData(quest);
	}
}
