// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BlueprintBindComponent.h"
#include "MoveLocationComponent.h"
#include "../Item/ItemDataManager.h"
#include "../Dialogue/DialogueManager.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameManager();

public:
	virtual void StartPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void GameEndSequence();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlueprintBindComponent* Blueprints = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMoveLocationComponent* MoveLocation = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItemDataManager* ItemDataManager = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UQuestManager* QuestDataManager = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDialogueManager* DialogueDataManager = nullptr;
};
