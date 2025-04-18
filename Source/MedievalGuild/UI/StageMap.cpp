// Fill out your copyright notice in the Description page of Project Settings.


#include "StageMap.h"
#include "Kismet/GameplayStatics.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Character/PlayerCharacter.h"
#include "../Object/StageActor.h"

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
	TArray<AActor*> findActorList;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AStageActor::StaticClass(), "Castle", findActorList);
	Cast<AStageActor>(findActorList[0])->ResetStageActor();
	MoveToArea("Castle");
}

void UStageMap::MoveToArea(FName toArea)
{
	ALocationActor* location = MoveLocation->GetLocationWithTag(toArea);
	if (location) {
		PlayerController->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		PlayerController->PlayerCharacter->SetActorLocation(location->GetActorLocation());
		PlayerController->PlayerCharacter->SetActorRotation(location->GetActorRotation());
		PlayerController->CurrentPlayerLocation = toArea;
		PlayerController->ScreenEffectUI->StartMoveStageAnimation();
	}
}
