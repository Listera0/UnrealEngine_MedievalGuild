// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrivalTriggerActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../QuestManager.h"
#include "../../Character/PlayerCharacter.h"
// Sets default values
AArrivalTriggerActor::AArrivalTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
}

void AArrivalTriggerActor::StartQuest(const float Radius,const int index)
{
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrivalTriggerActor::OnOverlapBegin);
	CollisionComponent->SetCapsuleRadius(Radius);

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	QuestIndex = index;
}


void AArrivalTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (!PlayerCharacter) return;
		UQuestManager::GetInstance()->OnPlayerArrived.Broadcast(QuestIndex);
		Destroy();
	}
}
