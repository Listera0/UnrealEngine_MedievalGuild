// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EItemType.h"

#include "Item_Base.generated.h"

UCLASS()
class MEDIEVALGUILD_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ItemFunc();


public: //getter 세팅
	inline EItemType GetItemType() const { return eItemType; }
	inline float GetPrice() const { return price; }
	inline FName GetName()const { return name; }
	inline FName GetDescription() const { return description;}
	inline int GetIndex() const { return index; }
	inline int GetCount() const { return count; }
	inline int GetHeight() const { return height; }
	inline int GetWeight() const { return weight; }

	inline bool Sell(int Count) { if (count - Count >= 0) { count -= Count; return true; }  return false;}
	inline void SetCount(int Count) { count = Count; }

protected: //컴포넌트 세팅
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* mesh = nullptr;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EItemType eItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int height = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int weight = 1;
};
