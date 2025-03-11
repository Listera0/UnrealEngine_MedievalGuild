#include "ItemDataManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

UItemDataManager* UItemDataManager::Instance = nullptr;

UItemDataManager::UItemDataManager()
{

    UItemData* NewItem = NewObject<UItemData>();
    NewItem->name = TEXT("Coin");
    NewItem->description = TEXT("Coin");
    NewItem->price = 1.0f;
    NewItem->index = 0;
    NewItem->width = 1;
    NewItem->height = 1;
    NewItem->weight = 0.1f;
    NewItem->eItemType = EItemType::None;
    NewItem->maxStack = 50;
    NewItem->bStackable = true;
    this->AddItemData(NewItem);



    FString FilePath = TEXT("TestitemData.json");
    this->SaveAllItemDataToJson(FilePath);
    this->LoadAllItemDataFromJson(FilePath);

}

UItemDataManager* UItemDataManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UItemDataManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

void UItemDataManager::AddItemData(UItemData* ItemData)
{
    if (ItemData)
    {
        bool IsValid = false;
        for (UItemData* ListItemData : ItemDataList)
        {
            if (ListItemData->index == ItemData->index)
            {
                IsValid = true;
                GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("AddItem Index is Valid!!"));
                break;
            }
        }
        if (!IsValid)
        {
            ItemDataList.Add(ItemData);
        }

    }
}

void UItemDataManager::SaveAllItemDataToJson(const FString& FilePath)
{
    TArray<TSharedPtr<FJsonValue>> JsonArray;

    for (UItemData* ItemData : ItemDataList)
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

        JsonObject->SetStringField(TEXT("ItemName"), ItemData->name);
        JsonObject->SetStringField(TEXT("ItemDescription"), ItemData->description);
        JsonObject->SetNumberField(TEXT("ItemIndex"), ItemData->index);
        JsonObject->SetNumberField(TEXT("ItemPrice"), ItemData->price);
        JsonObject->SetNumberField(TEXT("ItemWidth"), ItemData->width);
        JsonObject->SetNumberField(TEXT("ItemHeight"), ItemData->height);
        JsonObject->SetNumberField(TEXT("ItemWeight"), ItemData->weight);
        JsonObject->SetNumberField(TEXT("ItemMaxStack"), ItemData->maxStack);
        JsonObject->SetBoolField(TEXT("ItemStackable"), ItemData->bStackable);
        JsonObject->SetNumberField(TEXT("ItemType"), (int32)ItemData->eItemType);

        /*
        if (UItemData_Weapon* WeaponData = Cast<UItemData_Weapon>(ItemData))
        {
            JsonObject->SetNumberField(TEXT("WeaponDamage"), WeaponData->Damage);
            JsonObject->SetNumberField(TEXT("WeaponDurability"), WeaponData->Durability);
        }
        */

        JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JsonArray, Writer))
    {
        FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Item/Data/") + FilePath;

        FFileHelper::SaveStringToFile(OutputString, *CurrentFilePath);
    }
}


void UItemDataManager::LoadAllItemDataFromJson(const FString& FilePath)
{
    FString FileContents;
    if (FFileHelper::LoadFileToString(FileContents, *FilePath))
    {
        TArray<TSharedPtr<FJsonValue>> JsonArray;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);

        if (FJsonSerializer::Deserialize(Reader, JsonArray))
        {
            for (TSharedPtr<FJsonValue> JsonValue : JsonArray)
            {
                if (JsonValue->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
                    UItemData* LoadedItemData = nullptr;


                    EItemType ItemType = (EItemType)JsonObject->GetNumberField(TEXT("ItemType"));
                    switch (ItemType)
                    {
                    case EItemType::Weapon:
                        ;
                    default:
                        LoadedItemData = NewObject<UItemData>();
                        break;
                    }

                    // 공통 데이터 로드
                    LoadedItemData->name = JsonObject->GetStringField(TEXT("ItemName"));
                    LoadedItemData->description = JsonObject->GetStringField(TEXT("ItemDescription"));
                    LoadedItemData->index = JsonObject->GetNumberField(TEXT("ItemIndex"));
                    LoadedItemData->price = JsonObject->GetNumberField(TEXT("ItemPrice"));
                    LoadedItemData->width = JsonObject->GetNumberField(TEXT("ItemWidth"));
                    LoadedItemData->height = JsonObject->GetNumberField(TEXT("ItemHeight"));
                    LoadedItemData->weight = JsonObject->GetNumberField(TEXT("ItemWeight"));
                    LoadedItemData->maxStack = JsonObject->GetNumberField(TEXT("ItemMaxStack"));
                    LoadedItemData->bStackable = JsonObject->GetBoolField(TEXT("ItemStackable"));
                    LoadedItemData->eItemType = ItemType;

                    /*
                    // 무기 데이터 로드
                    if (UItemData_Weapon* WeaponData = Cast<UItemData_Weapon>(LoadedItemData))
                    {
                        WeaponData->Damage = JsonObject->GetNumberField(TEXT("WeaponDamage"));
                        WeaponData->Durability = JsonObject->GetNumberField(TEXT("WeaponDurability"));
                    }
                    */

                    ItemDataList.Add(LoadedItemData);
                }
            }
        }
    }
}

UStaticMesh* UItemDataManager::GetMeshForItem(const UItemData* item)
{
    FString MeshReference = FString::Printf(TEXT("%d_%s"), item->index, *item->name);
    FString MeshPath = FString::Printf(TEXT("/Game/Data/Item/Mesh/%s"), *MeshReference);

    UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);

    if (Mesh)
    {
        return Mesh;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh: %s"), *MeshPath);
        return nullptr;
    }
}

UMaterialInterface* UItemDataManager::GetMaterialForItem(const UItemData* item)
{
    FString MaterialReference = FString::Printf(TEXT("%d_%s"), item->index, *item->name);
    FString MaterialPath = FString::Printf(TEXT("/Game/Data/Item/Material/%s"), *MaterialReference);

    UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, *MaterialPath);

    if (Material)
    {
        return Material;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load material: %s"), *MaterialPath);
        return nullptr;
    }
}
