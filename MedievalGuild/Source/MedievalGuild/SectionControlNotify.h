// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SectionControlNotify.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API USectionControlNotify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

	// 목표 섹션 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SectionControl")
	FName NextSectionName;

private:
	class APlayerCharacter* OwnerCharacter = nullptr;
	bool bInitialized = false;
};
