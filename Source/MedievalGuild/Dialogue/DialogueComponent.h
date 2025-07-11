// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Dialogue.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALGUILD_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();

	void EndDialogue(int OptionIndex = -1);

	inline UDialogue* GetCurrentDialogue() const { return CurrentDialogue; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<int> MyDialogueList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<UDialogue*> DialogueList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDialogue* CurrentDialogue = nullptr;

private:
	class UQuestComponent* PlayerQuestComponent = nullptr;
};
