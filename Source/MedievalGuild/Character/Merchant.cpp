// Merchant.cpp
#include "Merchant.h"
#include "Components/CapsuleComponent.h"

AMerchant::AMerchant()
{
    PrimaryActorTick.bCanEverTick = true;

    

    Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    Collision->SetupAttachment(RootComponent);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Collision);

    Collision->OnComponentBeginOverlap.AddDynamic(this, &AMerchant::OnCapsuleBeginOverlap);
}

void AMerchant::BeginPlay()
{
    Super::BeginPlay();
}

void AMerchant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UItem__Object_Base* AMerchant::SellItem(int index, int Count)
{
    if (ItemInstances.Num() != Item_List.Num())
    {
        ItemInstances.Empty();
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemInstances size does not match Item_List size. Re-spawning items."));

        for (TSubclassOf<UItem__Object_Base> ItemClass : Item_List)
        {
            UItem__Object_Base* NewItem = NewObject<UItem__Object_Base>(this, ItemClass);
            if (NewItem)
            {
                ItemInstances.Add(NewItem);
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Created new item of class: %s"), *ItemClass->GetName()));
            }
        }
    }

    for (UItem__Object_Base* FoundItem : ItemInstances)
    {
        if (FoundItem && FoundItem->GetIndex() == index)
        {
            if (FoundItem->Sell(Count))
            {
                UItem__Object_Base* NewItem = NewObject<UItem__Object_Base>(this, FoundItem->GetClass());
                if (NewItem)
                {
                    NewItem->SetCount(Count);
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("New item created and sold. Remaining count: %d"), FoundItem->GetCount()));
                    return NewItem;
                }
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Not enough items to sell!"));
                return nullptr;
            }
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Item not found in merchant's inventory!"));
    return nullptr;
}




void AMerchant::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)  // 플레이어와 충돌 시
    {
        SellItem(1, 1);  // SellItem(1, 1) 호출
    }
}
