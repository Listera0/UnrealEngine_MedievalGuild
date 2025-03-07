// Merchant.cpp
#include "Merchant.h"
#include "Components/CapsuleComponent.h"
#include "../Item/ItemDataManager.h"

AMerchant::AMerchant()
{
    PrimaryActorTick.bCanEverTick = false;


    Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    Collision->SetupAttachment(RootComponent);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Collision);

    Collision->OnComponentBeginOverlap.AddDynamic(this, &AMerchant::OnCapsuleBeginOverlap);
}

void AMerchant::BeginPlay()
{
    Super::BeginPlay();

    UItemDataManager* ItemDataManager = UItemDataManager::GetInstance();
}

void AMerchant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


UItemData* AMerchant::SellItem(int index, int Count)
{
    for (UItemData* FoundItem : ItemDatas)
    {
        if (FoundItem && FoundItem->index == index)
        {
            if (true)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Item sold successfully. Remaining count: %d"), Count));



                UItemData* SoldItem = NewObject<UItemData>();

                return SoldItem;
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
