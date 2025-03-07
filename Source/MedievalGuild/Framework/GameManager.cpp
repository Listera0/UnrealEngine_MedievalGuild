// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

AGameManager::AGameManager()
{
	Blueprints = CreateDefaultSubobject<UBlueprintBindComponent>(FName("BlueprintBind"));
}

void AGameManager::StartPlay()
{
	Super::StartPlay();

}
