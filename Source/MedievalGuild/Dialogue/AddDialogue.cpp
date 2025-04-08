// Fill out your copyright notice in the Description page of Project Settings.


#include "AddDialogue.h"
#include "DialogueManager.h"
// Sets default values
AAddDialogue::AAddDialogue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAddDialogue::BeginPlay()
{
	Super::BeginPlay();
	
	for (UDialogue* Dialogue : DialogueList)
	{
		if (Dialogue)
		{
			UDialogueManager::GetInstance()->AddDialogue(Dialogue);
		}
	}
	UDialogueManager::GetInstance()->SaveAllDialogueToJson();
}
