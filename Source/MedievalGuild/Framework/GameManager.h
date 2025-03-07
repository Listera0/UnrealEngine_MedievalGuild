// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BlueprintBindComponent.h"

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

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlueprintBindComponent* Blueprints = nullptr;
};
