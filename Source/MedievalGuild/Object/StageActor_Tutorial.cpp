// Fill out your copyright notice in the Description page of Project Settings.


#include "StageActor_Tutorial.h"
#include "../Framework/PlayerCharacterController.h"

AStageActor_Tutorial::AStageActor_Tutorial()
{
	TutorialInteractOwner = CreateDefaultSubobject<USceneComponent>(FName("TutorialInteractOwner"));
	TutorialInteractOwner->SetupAttachment(RootComponent);
}

void AStageActor_Tutorial::BeginPlay()
{
	Super::BeginPlay();

	TutorialInitSetting();
}

void AStageActor_Tutorial::TutorialInitSetting()
{
	//TArray<UBoxComponent*> TutorialInteracts;
	int componentIndex = 1;

	for (USceneComponent* child : TutorialInteractOwner->GetAttachChildren())
	{
		UBoxComponent* BoxComponent = Cast<UBoxComponent>(child);
		if (BoxComponent) {
			BoxComponent->ComponentTags.Add(FName(*FString::Printf(TEXT("%d"), componentIndex))); componentIndex++;
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStageActor_Tutorial::TutorialPanelSetting);
			BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AStageActor_Tutorial::TutorialPanelClose);
			//TutorialInteracts.Add(BoxComponent); 
		}
	}
}

void AStageActor_Tutorial::TutorialPanelSetting(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%s"), *OtherComponent->GetName()));

	if (OtherComponent->ComponentHasTag("Player")) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%d"), FCString::Atoi(*OverlappedComponent->ComponentTags[0].ToString())));
		PlayerController->ScreenUI->ShowTutorialPanel(FCString::Atoi(*OverlappedComponent->ComponentTags[0].ToString()));
	}
}

void AStageActor_Tutorial::TutorialPanelClose(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%s"), *OtherComponent->GetName()));

	if (OtherComponent->ComponentHasTag("Player")) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%d"), FCString::Atoi(*OverlappedComponent->ComponentTags[0].ToString())));
		PlayerController->ScreenUI->ShowTutorialPanel(-1);
	}
}
