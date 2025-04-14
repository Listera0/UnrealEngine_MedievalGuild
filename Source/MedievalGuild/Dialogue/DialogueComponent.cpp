// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "DialogueManager.h"
#include "../Quest/QuestComponent.h"
#include "../Quest/QuestManager.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UDialogueComponent::EndDialogue(int OptionIndex)
{
	if (CurrentDialogue)
	{
		CurrentDialogue->bIsEndOfDialogue = true;
		if (CurrentDialogue->bIsDialogueOption)
		{
			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->DialogueOptions[OptionIndex].NextDialogueID);

			if (!CurrentDialogue)
				return;

			if (CurrentDialogue->DialogueOptions[OptionIndex].bGiveQuest)
			{
				if (!PlayerQuestComponent)
				{
					UWorld* World = GetWorld();
					if (World)
					{
						AActor* PlayerActor = World->GetFirstPlayerController()->GetPawn();
						if (PlayerActor)
						{
							PlayerQuestComponent = Cast<UQuestComponent>(PlayerActor->GetComponentByClass(UQuestComponent::StaticClass()));
						}
					}
				}

				if (PlayerQuestComponent)
				{
					PlayerQuestComponent->AddQuest(UQuestManager::GetInstance()->FindQuest(CurrentDialogue->DialogueOptions[OptionIndex].QuestIndex));
					//퀘스트 1개 안들어가는 버그 찾아서 수정
				}
			}
		}
		else
		{
			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->NextDialogueIndex);
		}

		if (CurrentDialogue)
		{
			CurrentDialogue->bIsEndOfDialogue = false;
			CurrentDialogue->UserSelectedOptionIndex = -1;
		}
	}
}


// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int index : MyDialogueList)
	{
		UDialogue* Dialogue = UDialogueManager::GetInstance()->FindDialogue(index);
		if (Dialogue)
		{
			DialogueList.Add(Dialogue);

		}
	}

	if (DialogueList.Num() > 0)
	{
		CurrentDialogue = DialogueList[0];
	}

	while (CurrentDialogue && CurrentDialogue->bIsEndOfDialogue)
	{
		if (CurrentDialogue->bIsDialogueOption)
		{
			if (CurrentDialogue->UserSelectedOptionIndex == -1)
			{
				CurrentDialogue = nullptr;
				break;
			}

			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->DialogueOptions[CurrentDialogue->UserSelectedOptionIndex].NextDialogueID);
		}
		else
		{
			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->NextDialogueIndex);
		}

		if(!CurrentDialogue)
			break;
	}


	if (CurrentDialogue && UDialogueManager::GetInstance()->IsDialogueOn(CurrentDialogue))
	{
		for (FString response : CurrentDialogue->Responses)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, response);
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("다음 퀘스트"));
		EndDialogue(0);
		if (CurrentDialogue)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, CurrentDialogue->DialogueText);
			for (FString response : CurrentDialogue->Responses)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, response);
			}
		}
	}

}

