// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "../Character/Enemy_1.h"
#include "../AI/EnemyAIController.h"
#include "AIController.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!OwnerEnemy) OwnerEnemy = Cast<AEnemy_1>(Cast<ACharacter>(TryGetPawnOwner()));
	if(OwnerEnemy && !EnemyController) EnemyController = Cast<AEnemyAIController>(OwnerEnemy->GetController());

	if (EnemyController) bIsMoving = !EnemyController->SuccessMove();
}
