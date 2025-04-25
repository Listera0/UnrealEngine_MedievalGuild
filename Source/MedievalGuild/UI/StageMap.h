// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Framework/MoveLocationComponent.h"
#include "../Framework/GameManager.h"
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

public:
	void StageMapInitSetting();

	UFUNCTION()
	void MoveToCastle();
	void MoveToArea(FName toArea);

	UPROPERTY(meta = (BindWidget))
	UButton* Castle = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LibraryText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LockText1 = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LockText2 = nullptr;

	class APlayerCharacterController* PlayerController = nullptr;
	AGameManager* GameManager = nullptr;
	UMoveLocationComponent* MoveLocation = nullptr;
};
