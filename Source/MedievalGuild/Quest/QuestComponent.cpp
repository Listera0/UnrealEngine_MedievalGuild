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
	if (IsPlayer)
	{
		UQuestManager::GetInstance()->GetPlayerQuset(MyQuestList);
	}
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
			if (Quest && Quest->CanStartQuest() && Quest->GetQuestStatus() == EQuestStatus::NotStarted)
			{
				UQuestComponent* QuestComponent = PlayerCharacter->FindComponentByClass<UQuestComponent>();
				if (QuestComponent)
				{
					Quest->PlayerGetQuest();
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

			if (InQuest->GetQuestStatus() == EQuestStatus::InProgress)
				StartQuestList.Add(InQuest);
		}
		else
		{
			bool IsAddQuest = UQuestManager::GetInstance()->AddQuestData(quest);
			if (IsAddQuest)
			{
				InQuest = UQuestManager::GetInstance()->FindQuest(quest->QuestIndex);
				MyQuestList.Add(InQuest);

				if (InQuest->GetQuestStatus() == EQuestStatus::InProgress)
					StartQuestList.Add(InQuest);

			}
			else
			{
				FString p = FString::Printf(TEXT("Error!! Not Add Quest [%d] "), quest->QuestIndex) + quest->QuestName;
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, p);
			}
		}
	}
}

void UQuestComponent::AddQuest(UQuest_Base* Quest)
{
	if (Quest && !MyQuestList.Contains(Quest))
	{
		MyQuestList.Add(Quest);
	}
}

void UQuestComponent::StartQuest(UQuest_Base* Quest)
{
	if (Quest->CanStartQuest())
	{
		if (Quest->GetQuestStatus() == EQuestStatus::NotStarted)
		{
			Quest->StartQuest();
			StartQuestList.Add(Quest);
		}
	}
}

void UQuestComponent::PrintMyQuests()
{
	for (UQuest_Base* quest : MyQuestList)
	{
		FString p = FString::Printf(TEXT("Add Quest [%d] "), quest->GetQuestIndex()) + quest->GetQuestData()->QuestName;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, p);
	}
}
