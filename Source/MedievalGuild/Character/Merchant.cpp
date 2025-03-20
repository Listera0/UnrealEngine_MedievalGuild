// Merchant.cpp
#include "Merchant.h"
#include "Components/CapsuleComponent.h"
#include "../Item/ItemDataManager.h"
#include "../Quest/QuestComponent.h"

AMerchant::AMerchant()
{
    PrimaryActorTick.bCanEverTick = false;


    Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
    Collision->SetupAttachment(RootComponent);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Collision);

    Collision->OnComponentBeginOverlap.AddDynamic(this, &AMerchant::OnCapsuleBeginOverlap);

    QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

}

void AMerchant::BeginPlay()
{
    Super::BeginPlay();

    UItemDataManager* ItemDataManager = UItemDataManager::GetInstance();
    ItemDatas = ItemDataManager->GetItemDataList();
}


FInventoryData* AMerchant::SellItem(int index, int Count)
{
    FInventoryData* item = HasItem(index, false);
    if(item)
    {
        if (item->ItemCount >= Count)
        {
            RemoveItemToInv(item->ItemData,Count,true);
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Item sold successfully.")));
            return item;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Not enough ItemCount")));
            return nullptr;
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Item not found in merchant's inventory!"));
    return nullptr;
}




void AMerchant::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)  // 플레이어와 충돌 시
    {
        SellItem(0, 1);  // SellItem(1, 1) 호출
        QuestComponent->GiveQuestToPlayer(OtherActor);
    }
}
