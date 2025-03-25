// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "BlueprintBindComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALGUILD_API UBlueprintBindComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlueprintBindComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemSlotImgClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemBaseClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> ItemMoveSlotClass;
	UPROPERTY()
	TSubclassOf<UUserWidget> EquipmentWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> ContainerWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> StorageWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> TradeWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> MerchantInventoryWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> GearWidget;
		
};
