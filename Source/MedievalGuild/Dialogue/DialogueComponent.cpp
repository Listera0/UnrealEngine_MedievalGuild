// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "DialogueManager.h"
#include "../Quest/QuestComponent.h"
#include "../Quest/QuestManager.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Character/PlayerCharacter.h"

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

			CurrentDialogue->UserSelectedOptionIndex = OptionIndex;

			if (CurrentDialogue->DialogueOptions[OptionIndex].bGiveQuest)
			{

				if (!PlayerQuestComponent)
				{
					UWorld* World = GetWorld();
					if (World)
					{
						APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(World->GetFirstPlayerController());
						if (PlayerController)
						{
							PlayerQuestComponent = PlayerController->PlayerCharacter->QuestComponent;
						}
					}
				}

				if (PlayerQuestComponent)
				{
					PlayerQuestComponent->AddQuest(UQuestManager::GetInstance()->FindQuest(CurrentDialogue->DialogueOptions[OptionIndex].QuestIndex));
				}
			}

			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->DialogueOptions[OptionIndex].NextDialogueID);
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

	while (CurrentDialogue && CurrentDialogue->bIsEndOfDialogue) // 진행중인 대화 찾기
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

		if (!CurrentDialogue)
			break;
	}
}