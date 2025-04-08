// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveItemRecipe.h"
#include "../ItemDataManager.h"
// Sets default values
ASaveItemRecipe::ASaveItemRecipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASaveItemRecipe::BeginPlay()
{
	Super::BeginPlay();

	for (UItemRecipe* recipe : ItemRecipeList)
	{
		UItemDataManager::GetInstance()->AddItemRecipe(recipe);
	}
	UItemDataManager::GetInstance()->SaveAllItemRecipeToJson();
}
