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

protected:
	virtual void Tick(float DeltaTime) override;

	class APlayerCharacterController* PlayerController;

	void SetLanguageOption();
	void SetSelectLanguage();

public:
	FText TranslateTexts(FText text);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FName> TranslateLanguages;
	UPROPERTY(VisibleAnywhere)
	int SelectLanguageIndex;

	TMap<FString, FString> TranslateData;
};
