// Fill out your copyright notice in the Description page of Project Settings.


#include "SectionControlNotify.h"
#include "../Character/PlayerCharacter.h"

void USectionControlNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!bInitialized) {
		OwnerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		bInitialized = true;
	}
	
	if (OwnerCharacter) {
		OwnerCharacter->OnSectionJumpReady(this);
	}
}

void USectionControlNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (OwnerCharacter) {
		OwnerCharacter->OnSectionJumpEnd(this);
	}
}
