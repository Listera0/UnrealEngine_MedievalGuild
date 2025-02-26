// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Item/Item_Base.h"

#include "Merchant.generated.h"

UCLASS()
class MEDIEVALGUILD_API AMerchant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMerchant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual AItem_Base* SellItem(AItem_Base* Item, int Count);

private:
	TArray<AItem_Base*> Item_List;

};
