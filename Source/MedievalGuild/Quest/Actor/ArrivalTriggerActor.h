// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrivalTriggerActor.generated.h"

UCLASS()
class MEDIEVALGUILD_API AArrivalTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrivalTriggerActor();

	void StartQuest(const float Radius, const int index);


protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	class UCapsuleComponent* CollisionComponent;

	int QuestIndex = -1;
};
