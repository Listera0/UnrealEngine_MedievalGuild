// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest_Base.h"
#include "QuestManager.h"

#include "QuestAddActor.generated.h"

UCLASS()
class MEDIEVALGUILD_API AQuestAddActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestAddActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest|Add")
	TArray<UQuestData_Base*> QuestAddList;

};
