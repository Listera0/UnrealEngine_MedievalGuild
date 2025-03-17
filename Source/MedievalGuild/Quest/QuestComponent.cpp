// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "../Character/PlayerCharacter.h"
#include "../Quest/QuestManager.h"

UQuestComponent::UQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	InitQuest();
}


// Called every frame
void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UQuestComponent::GiveQuestToPlayer(AActor* PlayerActor)
{
	if (PlayerActor && PlayerActor->IsA(APlayerCharacter::StaticClass()))
	{
		GiveQuestToPlayer_Internal(PlayerActor);
	}
}

void UQuestComponent::GiveQuestToPlayer_Internal(AActor* PlayerActor)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerActor);
	if (PlayerCharacter)
	{
		for (UQuest_Base* Quest : MyQuestList)
		{
			if (Quest)
			{
				UQuestComponent* QuestComponent = PlayerCharacter->FindComponentByClass<UQuestComponent>();
				if (QuestComponent)
				{
					QuestComponent->AddQuest(Quest);
				}
			}
		}
	}
}

void UQuestComponent::InitQuest()
{
	for (UQuestData_Base* quest : SetQuestList)
	{
		UQuest_Base* InQuest = UQuestManager::GetInstance()->FindQuest(quest->QuestIndex);
		if (InQuest)
		{
			MyQuestList.Add(InQuest);
		}
	}
}

void UQuestComponent::AddQuest(UQuest_Base* Quest)
{
	if (Quest)
	{
		MyQuestList.Add(Quest);
	}
}