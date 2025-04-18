// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "DebugManager.generated.h"

UCLASS()
class MEDIEVALGUILD_API ADebugManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADebugManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bDebugMode;
	float TickDebugger;
};
