// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ItemSpawnOption.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALGUILD_API UItemSpawnOption : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemSpawnOption();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// 배열 인덱스 받아서 그중 랜덤으로 아이템 선택
};
