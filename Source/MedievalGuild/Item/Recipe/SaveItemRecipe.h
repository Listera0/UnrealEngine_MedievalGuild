// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Recipe/ItemRecipe.h"

#include "SaveItemRecipe.generated.h"

UCLASS()
class MEDIEVALGUILD_API ASaveItemRecipe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveItemRecipe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Recipe")
	TArray<UItemRecipe*> ItemRecipeList;
};
