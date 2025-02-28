// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	NotStarted UMETA(DisplayName = "NotStarted"),
	InProgress UMETA(DisplayName = "InProgress"),
	Completed UMETA(DisplayName = "Completed")
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Arrive UMETA(DisplayName = "Arrive"),
	Item UMETA(DisplayName = "Item"),
	KillCount UMETA(DisplayName = "KillCount"),
	None UMETA(DisplayName = "None")
};