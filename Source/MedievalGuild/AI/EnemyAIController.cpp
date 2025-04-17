// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "../Character/Enemy_1.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Navigation/PathFollowingComponent.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	if (SightConfig)
	{
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = 1200.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;
		SightConfig->SetMaxAge(5.0f);

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		//UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
		//RunBehaviorTree(BehaviorTree);
		//BlackboardComponent->SetValueAsVector("OriginLocation", GetPawn()->GetActorLocation());
	}
	OwnerEnemy = Cast<AEnemy_1>(GetPawn());
	MoveLocation = GetPawn()->GetActorLocation();
	OwnerEnemy->GetNextPatrolLocation();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemyMoveSequence(DeltaTime);
}

void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag("Player") && !Actor->ActorHasTag("Dead")) {
		if (Stimulus.WasSuccessfullySensed()) {
			if (Actor->ActorHasTag("Player") && !ActorHasTag("Dead")) {
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Detected: %s"), *Actor->GetName()));
				TargetActor = Actor;
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Lost sight of: %s"), *Actor->GetName()));
			TargetActor = nullptr;
		}
	}
}

void AEnemyAIController::EnemyMoveSequence(float DeltaTime)
{
	if (TargetActor) {
		EnemyState = 1;
		PatrolTimer = 0.0f;
		SearchTimer = 0.0f;
		SearchTotalTimer = 0.0f;
		MoveLocation = TargetActor->GetActorLocation();
	}
	else {
		if (EnemyState == 1) EnemyState = 2;
	}

	if(!OwnerEnemy->CheckAttackAnim()) MoveToLocation(MoveLocation);
	if (!SuccessMove()) return;

	if (EnemyState == 0) {
		PatrolTimer += DeltaTime;

		if (PatrolTimer >= 5.0f) {
			MoveLocation = OwnerEnemy->GetNextPatrolLocation();
			PatrolTimer = 0.0f;
		}
	}
	else if (EnemyState == 1) {
		if (!OwnerEnemy->CheckAttackAnim()) OwnerEnemy->AttackAction();
	}
	else if (EnemyState == 2) {
		SearchTimer += DeltaTime;
		SearchTotalTimer += DeltaTime;

		if (SearchTotalTimer >= 10.0f) {
			SearchTotalTimer = 0.0f;
			SearchTimer = 0.0f;
			EnemyState = 0;
		}
		else if (SearchTimer >= 2.0f) {
			FNavLocation RandomLocation;
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			NavSys->GetRandomReachablePointInRadius(MoveLocation, 150.0f, RandomLocation);
			MoveLocation = RandomLocation.Location;
			SearchTimer = 0.0f;
		}
	}
}

bool AEnemyAIController::SuccessMove()
{
	bool returnValue = FVector::DistSquared(MoveLocation, OwnerEnemy->GetActorLocation()) <= 20000.0f ? true : false;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("dist: %.1f"), FVector::DistSquared(MoveLocation, OwnerEnemy->GetActorLocation())));
	return returnValue;
}


