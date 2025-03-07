// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

#include "../Framework/GameManager.h"
#include "ContainerWidget.h"
#include "BuyWidget.h"

#include "Trade.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UTrade : public UUserWidget
{
	GENERATED_BODY()

public:
	UTrade(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void TradePanelInitSetting();

protected:
	AGameManager* GameManager = nullptr;
	UBlueprintBindComponent* Blueprints = nullptr;

public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* TradeSlot;
};
