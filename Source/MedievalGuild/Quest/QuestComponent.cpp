// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "../Character/PlayerCharacter.h"
#include "../Quest/QuestManager.h"


UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	MyQuestList.Empty();
	StartQuestList.Empty();
	SetQuestList.Empty();

	if (IsPlayer)
	{
		UQuestManager::GetInstance()->GetPlayerQuset(MyQuestList);

		if (!MyQuestList.IsEmpty())
		{
			for (UQuest_Base* quest : MyQuestList)
			{
				quest->StartQuest(GetWorld());
			}
		}

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
			if (Quest && Quest->CanStartQuest() && !Quest->IsPlayerGet())
			{
				UQuestComponent* QuestComponent = PlayerCharacter->FindComponentByClass<UQuestComponent>();
				if (QuestComponent)
				{
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Player Get Quest"));
					Quest->PlayerGetQuest();
					QuestComponent->AddQuest(Quest);
				}
			}
		}
	}
}

void UQuestComponent::InitQuest()
{
	if (!SetQuestList.IsEmpty())
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
			Quest->StartQuest(GetWorld());
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

void UQuestComponent::GetMyQuestDatas(TArray<UQuest_Base*>& datalist)
{
	if (!MyQuestList.IsEmpty())
	{
		for (UQuest_Base* quest : MyQuestList)
		{
			if (quest == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Quest is nullptr!"));
				continue;
			}

			datalist.Add(quest);
		}
	}
}
