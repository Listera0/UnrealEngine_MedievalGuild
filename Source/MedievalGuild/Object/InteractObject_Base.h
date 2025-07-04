// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../Item/ItemDataManager.h"
#include "../Object/InventoryData.h"
#include "../Object/IInteractInterface.h"
#include "InteractObject_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API AInteractObject_Base : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractObject_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	USceneComponent* RootComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh = nullptr;
public:

	TArray<FInventoryData*> ContainerInventory;
	bool bIsInit;

	UPROPERTY(EditAnywhere, Category = "Item")
	bool bFollowDataSet;
	UPROPERTY(EditAnywhere, Category = "Item")
	int DataSetIndex;
	UPROPERTY(EditAnywhere, Category = "Item")
	TMap<int, int> ContainerIndex;
	UPROPERTY(EditAnywhere, Category = "Item")
	FVector2D ContainerSize;
	UPROPERTY(EditAnywhere)
	FName ObjectName;

	float InteractDistance = 0.0f;

public:
	void SetContainerUI();
	void InteractableItemSetting();

	void AddItemToInv(FInventoryData* data);
	void RemoveItemToInv(FVector2D location, int count, bool withDelete);
	void RemoveItemToInv(UItemData* item, int count, bool withDelete);
	void MoveItemIndex(FVector2D to, FInventoryData* data); // 외부용
	void MoveItemIndex(FVector2D from, FVector2D to); // 내부용
	virtual void SetInteractDistance(float distance) override { InteractDistance = distance; };
	virtual float GetInteractDistance() override { return InteractDistance; };

	FInventoryData* HasItem(int itemIndex, bool checkMaxStack);
	FInventoryData* FindItemWithLocation(FVector2D location);

	
};
