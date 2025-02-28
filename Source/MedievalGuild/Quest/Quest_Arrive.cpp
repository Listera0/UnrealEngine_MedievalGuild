// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest_Arrive.h"
#include "Kismet/GameplayStatics.h"

bool UQuest_Arrive::CheckQuest(int index)
{
	if (!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	}

	if (PlayerController)
	{
		FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		float Distance = FVector::Dist(PlayerLocation, TargetLocation);

		if (Distance <= AcceptableRadius)
		{
			CompleteQuest();
			return true;
		}
	}

	return false;
}
