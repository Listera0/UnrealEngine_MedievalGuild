// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dialogue.h"
#include "DialogueManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UDialogueManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	static UDialogueManager* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	void ClearUp();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	void AddDialogue(UDialogue* Dialogue);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	void SaveAllDialogueToJson();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	void LoadAllDialogueFromJson(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	TArray<UDialogue*> GetDialogueList() const { return DialogueList; }

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	UDialogue* const FindDialogue(int DialogueIndex);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Manager")
	bool IsDialogueOn(UDialogue* dialogue);

private:
	static UDialogueManager* Instance;

	UPROPERTY()
	TArray<UDialogue*> DialogueList;

	FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Dialogue/Data/");
};
