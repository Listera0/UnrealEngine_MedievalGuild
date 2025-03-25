// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrivalTriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerArrived);
UCLASS()
class MEDIEVALGUILD_API AArrivalTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrivalTriggerActor();

	void SetRadius(float Radius);
protected:
	// 충돌 시작 시 호출되는 함수
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnPlayerArrived OnPlayerArrived;

protected:
	// 도착지 충돌 영역을 나타낼 콜리전 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	class UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	float AcceptableRadius;


};
