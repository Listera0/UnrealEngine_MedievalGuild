// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsMoving;

	class AEnemy_1* OwnerEnemy = nullptr;
	class AEnemyAIController* EnemyController = nullptr;
};
