// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject_Base.h"

// Sets default values
AInteractObject_Base::AInteractObject_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootComponent"));
	SetRootComponent(RootComponent);

	InteractArea = CreateDefaultSubobject<USphereComponent>(FName("InteractArea"));
	InteractArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractObject_Base::BeginPlay()
{
	Super::BeginPlay();

	TArray<UItemData*> itemDatas = UItemDataManager::GetInstance()->GetItemDataList();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("%d"), itemDatas.Num()));
}

// Called every frame
void AInteractObject_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

