// Fill out your copyright notice in the Description page of Project Settings.


#include "Merchant.h"

// Sets default values
AMerchant::AMerchant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMerchant::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMerchant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AItem_Base* AMerchant::SellItem(AItem_Base* Item, int Count)
{
    int index;

    if (Item_List.Find(Item, index))
    {
        AItem_Base& FoundItem = *Item_List[index];

        if (FoundItem.Sell(Count))
        {
            return &FoundItem;
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Not enough items to sell!"));
            }

            return nullptr;
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Item not found in merchant's list!"));
        }

        return nullptr;
    }
}
