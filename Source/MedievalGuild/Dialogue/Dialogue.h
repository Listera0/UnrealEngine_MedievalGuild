// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Dialogue.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString OptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int NextDialogueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bGiveQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int QuestIndex;

	FDialogueOption()
		: NextDialogueID(-1),
		bGiveQuest(false),
		QuestIndex(-1) { }
};

UCLASS()
class MEDIEVALGUILD_API UDialogue : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int DialogueIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString DialogueText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<int> CompleteQuestIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> Responses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsDialogueOption;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int NextDialogueIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueOption> DialogueOptions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int UserSelectedOptionIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsEndOfDialogue;
};