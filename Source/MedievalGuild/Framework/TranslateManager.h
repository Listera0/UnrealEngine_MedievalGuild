// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TranslateManager.generated.h"

UCLASS()
class MEDIEVALGUILD_API ATranslateManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATranslateManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void TranslateTexts();
	void TranslateTexts(FText text);

	class APlayerCharacterController* PlayerController;

	TArray<FName> TranslateLanguages;
	int SelectLanguageIndex;
};
