// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrivalTriggerActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArrivalTriggerActor::AArrivalTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	CollisionComponent->SetCapsuleRadius(AcceptableRadius);
}

void AArrivalTriggerActor::SetRadius(float Radius)
{
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrivalTriggerActor::OnOverlapBegin);
	AcceptableRadius = Radius;
	CollisionComponent->SetCapsuleRadius(AcceptableRadius);
}

void AArrivalTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APlayerController::StaticClass()))
	{
		OnPlayerArrived.Broadcast();
	}
}



