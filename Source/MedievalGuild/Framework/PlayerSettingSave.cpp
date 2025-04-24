// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSettingSave.h"

void UPlayerSettingSave::SavePlayerSetting(int lan, int sen, int fov, bool fulls)
{
	LanguageIndex = lan;
	SensitiveValue = sen;
	FOVValue = fov;
	FullScreenValue = fulls;
}

void UPlayerSettingSave::LoadPlayerSetting(int& lan, int& sen, int& fov, bool& fulls)
{
	lan = LanguageIndex;
	sen = SensitiveValue;
	fov = FOVValue;
	fulls = FullScreenValue;
}
