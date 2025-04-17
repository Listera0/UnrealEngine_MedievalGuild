// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "../Quest/QuestManager.h"

AGameManager::AGameManager()
{
	Blueprints = CreateDefaultSubobject<UBlueprintBindComponent>(FName("BlueprintBind"));
	MoveLocation = CreateDefaultSubobject<UMoveLocationComponent>(FName("MoveLocation"));
}

void AGameManager::StartPlay()
{
	Super::StartPlay();
	ItemDataManager = UItemDataManager::GetInstance();	
	QuestDataManager = UQuestManager::GetInstance();
	DialogueDataManager = UDialogueManager::GetInstance();

	ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));
	DirectionalLight->GetLightComponent()->SetIntensity(0.0f);
}

void AGameManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ItemDataManager)
		ItemDataManager->ClearUp();
	if (QuestDataManager)
		QuestDataManager->CleanUp();
	if (DialogueDataManager)
		DialogueDataManager->ClearUp();

	Super::EndPlay(EndPlayReason);
}

void AGameManager::GameEndSequence()
{

	if (ItemDataManager)
		ItemDataManager->ClearUp();
	if (QuestDataManager)
	{
		//QuestDataManager->SaveAllQuestDataToJson();
		QuestDataManager->CleanUp();
	}
	if (DialogueDataManager)
	{
		//DialogueDataManager->SaveAllDialogueToJson();
		DialogueDataManager->ClearUp();
	}
}
