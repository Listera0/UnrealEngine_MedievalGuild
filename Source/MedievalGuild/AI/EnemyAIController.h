// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy|AI")
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|AI")
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy|AI")
	UAIPerceptionComponent* AIPerceptionComponent;
	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void EnemyMoveSequence(float DeltaTime);
	bool SuccessMove();
	
	class AEnemy_1* OwnerEnemy;

	bool bInitFinish;
	int EnemyState = 0;
	float SearchTimer = 0.0f;
	float SearchTotalTimer = 0.0f;
	float PatrolTimer = 0.0f;
	FVector MoveLocation;
	AActor* TargetActor = nullptr;
};
