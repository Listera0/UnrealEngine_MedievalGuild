// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugManager.h"

// Sets default values
ADebugManager::ADebugManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ADebugManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADebugManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDebugMode) {
		if (TickDebugger != 0.0f) {
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("%.1f"), TickDebugger));
			if (TickDebugger >= 100.0f) TickDebugger = 0.0f;
		}
	}
}