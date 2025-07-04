// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "QuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALGUILD_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestToPlayer(AActor* PlayerActor);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuest(UQuest_Base* Quest);

	void StartQuest(UQuest_Base* Quest);

	void PrintMyQuests();

	void GetMyQuestDatas(TArray<class UQuest_Base*>& datalist);

	inline void PlayerComponent() { IsPlayer = true; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void GiveQuestToPlayer_Internal(AActor* PlayerActor);
		
	void InitQuest();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<class UQuestData_Base*> SetQuestList;

private:
	UPROPERTY(EditAnywhere, Category = "Quest")
	TArray<class UQuest_Base*> MyQuestList;

	TArray<class UQuest_Base*> StartQuestList;

	bool IsPlayer = false;
};
