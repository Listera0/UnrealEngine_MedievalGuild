// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../Framework/PlayerCharacterController.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter && PlayerController) {
		if (PlayerCharacter->PlayerMoveState == MoveState::Stealth) { 
			bIsStealth = true;
			MoveSpeed = PlayerCharacter->GetVelocity().Size() / 3.0f;
		}
		else if (PlayerCharacter->PlayerMoveState == MoveState::Idle) {
			bIsStealth = false;
			MoveSpeed = PlayerCharacter->GetVelocity().Size() / 7.5f;
		}
		else {
			bIsStealth = false;
			MoveSpeed = PlayerCharacter->GetVelocity().Size() / 6.0f;
		}
	}
}
