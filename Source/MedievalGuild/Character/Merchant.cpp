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


    UItemData* NewItem = NewObject<UItemData>();
    NewItem->name = TEXT("Shield");
    NewItem->description = TEXT("A protective shield.");
    NewItem->price = 75.0f;
    NewItem->index = 2;
    NewItem->count = 1;
    NewItem->height = 3;
    NewItem->weight = 6;
    NewItem->eItemType = EItemType::Clothes;

    ItemDataManager->AddItemData(NewItem);

    FString FilePath = FPaths::ProjectSavedDir() / TEXT("itemData.json");
    ItemDataManager->SaveAllItemDataToJson(FilePath);
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemData Save"));

    ItemDataManager->LoadAllItemDataFromJson(FilePath);
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemData Load"));
    for (UItemData* LoadedItem : ItemDataManager->GetItemDataList())
    {
        UE_LOG(LogTemp, Log, TEXT("Loaded Item: %s"), *LoadedItem->name);
    }
}

void AMerchant::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

AItem_Base* AMerchant::SellItem(int index, int Count)
{
    if (ItemInstances.Num() != Item_List.Num())
    {
        ItemInstances.Empty();
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemInstances size does not match Item_List size. Re-spawning items."));

        for (TSubclassOf<AItem_Base> ItemClass : Item_List)
        {
            AItem_Base* NewItem = GetWorld()->SpawnActor<AItem_Base>(ItemClass);
            if (NewItem)
            {
                NewItem->SetActorHiddenInGame(true);
                ItemInstances.Add(NewItem);
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Spawned new item of class: %s"), *ItemClass->GetName()));
            }
        }
    }

    for (AItem_Base* FoundItem : ItemInstances)
    {
        if (FoundItem && FoundItem->GetIndex() == index)
        {
            if (FoundItem->Sell(Count))
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Item sold successfully. Remaining count: %d"), FoundItem->GetCount()));

                AItem_Base* NewItem = GetWorld()->SpawnActor<AItem_Base>(FoundItem->GetClass());
                if (NewItem)
                {
                    NewItem->SetCount(Count);
                    NewItem->SetActorHiddenInGame(true);
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Create Item. Item count: %d"), NewItem->GetCount()));
                    return NewItem;
                }
                else
                {
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Failed to spawn new item."));
                    return nullptr;
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
