// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Object/InteractObject_Base.h"
#include "../Character/Enemy_1.h"
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

	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	virtual void Tick(float DeltaTime) override;

	int GetRandomPatrolLocation(int ignore);
	FVector GetPatrolLocationVector(int index);

	void InitStageActor();
	void ResetStageActor();

	class APlayerCharacterController* PlayerController;

	USceneComponent* RootComponents = nullptr;
	USceneComponent* SpawnPointOwner = nullptr;
	USceneComponent* SpawnAreaOwner = nullptr;
	USceneComponent* InteractContainerOwner = nullptr;
	USceneComponent* ExtractAreaOwner = nullptr;
	USceneComponent* EnemySpawnOwner = nullptr;
	USceneComponent* EnemyPatrolOwner = nullptr;

	TArray<USceneComponent*> SpawnPoints;
	TArray<AInteractObject_Base*> SpawnedItems;
	TArray<AInteractObject_Base*> SpawnedContainers;
	TArray<AEnemy_1*> SpawnedEnemys;

	bool bIsInteractExtractionArea;
	float extractTimer;

	UPROPERTY(EditAnywhere)
	FName LocationName;

	UPROPERTY()
	TSubclassOf<AEnemy_1> EnemyClass;
};
