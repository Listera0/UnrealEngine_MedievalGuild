// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "DialogueManager.h"
// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UDialogueComponent::EndDialogue(int NextDialogueIndex)
{
	if (CurrentDialogue)
	{
		if (CurrentDialogue->bIsDialogueOption)
		{
			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(NextDialogueIndex);
		}
		else
		{
			CurrentDialogue = UDialogueManager::GetInstance()->FindDialogue(CurrentDialogue->NextDialogueIndex);
		}
		CurrentDialogue->bIsEndOfDialogue = true;
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
			if (!Dialogue->bIsEndOfDialogue && !CurrentDialogue)
			{
				CurrentDialogue = Dialogue;
			}
		}
	}
}

