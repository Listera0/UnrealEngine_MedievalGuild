// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenEffectWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UScreenEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	UWidgetAnimation* GetAnimationByName(FName AnimName);

public:
	void StartDeathAnimation();
	void StartMoveStageAnimation();
	void EndAnimation(float time);
	bool CheckPlayingAnimation();

	UPROPERTY()
	UWidgetAnimation* DeathAnim;
	UPROPERTY()
	UWidgetAnimation* MoveAnim;
};
