// Fill out your copyright notice in the Description page of Project Settings.


#include "StageMap.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Character/PlayerCharacter.h"

void UStageMap::NativeConstruct()
{
	Super::NativeConstruct();

}

void UStageMap::StageMapInitSetting()
{
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	GameManager = Cast<AGameManager>(UGameplayStatics::GetGameMode(GetWorld()));
	MoveLocation = GameManager->MoveLocation;

	Castle->OnClicked.AddDynamic(this, &UStageMap::MoveToCastle);
}

void UStageMap::MoveToCastle()
{
	MoveToArea("Castle");
}

void UStageMap::MoveToArea(FName toArea)
{
	ALocationActor* location = MoveLocation->GetLocationWithTag(toArea);
	if (location) {
		PlayerController->PlayerCharacter->SetActorLocation(location->GetActorLocation());
		PlayerController->CurrentPlayerLocation = toArea;
	}
}
