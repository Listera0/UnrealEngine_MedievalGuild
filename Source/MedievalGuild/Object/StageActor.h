// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StageActor.generated.h"

UCLASS()
class MEDIEVALGUILD_API AStageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USceneComponent* RootComponents = nullptr;
	USceneComponent* SpawnPointOwner = nullptr;
	USceneComponent* SpawnAreaOwner = nullptr;
	USceneComponent* ExtractAreaOwner = nullptr;

	TArray<USceneComponent*> SpawnPoints;

	bool bIsInteractExtractionArea;
};
