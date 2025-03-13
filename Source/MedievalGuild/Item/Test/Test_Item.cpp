// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Item.h"
#include "../ItemDataManager.h"
// Sets default values
ATest_Item::ATest_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATest_Item::BeginPlay()
{
	Super::BeginPlay();
	TArray<UItemData*> Itemlist = UItemDataManager::GetInstance()->GetItemDataList();
    UItemData* item = nullptr;

    for (UItemData* FoundItem : Itemlist)
    {
        if (FoundItem->index == 0)
        {
            item = FoundItem;
        }
    }
	
    if (UItemDataManager::GetInstance()->GetMeshForItem(item))
    {
        mesh->SetStaticMesh(UItemDataManager::GetInstance()->GetMeshForItem(item));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Not mesh!!"));
    }
    if (UItemDataManager::GetInstance()->GetMaterialForItem(item))
    {
       mesh->SetMaterial(0,UItemDataManager::GetInstance()->GetMaterialForItem(item));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Not material!!"));
    }
}

// Called every frame
void ATest_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

