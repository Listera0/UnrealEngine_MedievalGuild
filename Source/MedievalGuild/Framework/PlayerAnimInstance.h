// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Character/PlayerCharacter.h"

#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsStealth;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	APlayerCharacterController* PlayerController = nullptr;

};
