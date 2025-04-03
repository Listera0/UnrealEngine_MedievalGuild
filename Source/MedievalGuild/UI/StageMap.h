// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Framework/MoveLocationComponent.h"
#include "../Framework/GameManager.h"
#include "Components/Button.h"
#include "StageMap.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UStageMap : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Hideout = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* Castle = nullptr;

public:
	void StageMapInitSetting();

	UFUNCTION()
	void MoveToCastle();

	class APlayerCharacterController* PlayerController = nullptr;
	AGameManager* GameManager = nullptr;
	UMoveLocationComponent* MoveLocation = nullptr;
};
