// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "../Item/ItemDataManager.h"

#include "InteractObject_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API AInteractObject_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractObject_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	USceneComponent* RootComponent = nullptr;
	USphereComponent* InteractArea = nullptr;
};
