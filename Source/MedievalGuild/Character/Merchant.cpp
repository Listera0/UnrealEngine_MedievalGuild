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

AItem_Base* AMerchant::SellItem(int index, int Count)
{
    for (int i = 0; i < Item_List.Num(); ++i)
    {
        TSubclassOf<AItem_Base> ItemClass = Item_List[i];

        AItem_Base* FoundItem = GetWorld()->SpawnActor<AItem_Base>(ItemClass);

        if (FoundItem && FoundItem->GetIndex() == index)
        {
            if (FoundItem->Sell(Count))
            {
                AItem_Base* NewItem = GetWorld()->SpawnActor<AItem_Base>(ItemClass);

                if (NewItem)
                {
                    NewItem->SetCount(Count);
                    if (GEngine)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("sell!"));
                    }
                    return NewItem;
                }
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
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Item not found in merchant's list!"));
    }

    return nullptr;
}

void AMerchant::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)  // 플레이어와 충돌 시
    {
        SellItem(1, 1);  // SellItem(1, 1) 호출
    }
}
