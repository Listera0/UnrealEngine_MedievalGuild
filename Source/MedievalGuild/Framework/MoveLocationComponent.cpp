// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveLocationComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMoveLocationComponent::UMoveLocationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveLocationComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALocationActor::StaticClass(), FoundActors);
	for (AActor* actor : FoundActors) {
		MoveLocations.Add(Cast<ALocationActor>(actor));
	}
}


// Called every frame
void UMoveLocationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ALocationActor* UMoveLocationComponent::GetLocationWithTag(FName tag)
{
	for (ALocationActor* location : MoveLocations) {
		if (location->ActorHasTag(tag)) return location;
	}

	return nullptr;
}

