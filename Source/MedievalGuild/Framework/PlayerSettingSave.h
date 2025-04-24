// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSettingSave.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UPlayerSettingSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SavePlayerSetting(int lan, int sen, int fov, bool fulls);
	void LoadPlayerSetting(int& lan, int& sen, int& fov, bool& fulls);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int LanguageIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int SensitiveValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int FOVValue;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	bool FullScreenValue;

};
