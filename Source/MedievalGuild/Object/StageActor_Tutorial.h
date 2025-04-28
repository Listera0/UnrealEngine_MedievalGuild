// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Object/StageActor.h"
#include "StageActor_Tutorial.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API AStageActor_Tutorial : public AStageActor
{
	GENERATED_BODY()
	
public:
	AStageActor_Tutorial();

protected:
	virtual void BeginPlay() override;
	
	void TutorialInitSetting();
	UFUNCTION()
	void TutorialPanelSetting(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TutorialPanelClose(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

public:
	//class APlayerCharacterController* PlayerController = nullptr;

	USceneComponent* TutorialInteractOwner = nullptr;
};
