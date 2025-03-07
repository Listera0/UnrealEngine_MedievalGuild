#include "ItemDataManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

UItemDataManager* UItemDataManager::Instance = nullptr;

UItemDataManager::UItemDataManager()
{
    /*
    UItemData* NewItem = NewObject<UItemData>();
    NewItem->name = TEXT("B");
    NewItem->description = TEXT("B");
    NewItem->price = 75.0f;
    NewItem->index = 4;
    NewItem->width = 1;
    NewItem->height = 3;
    NewItem->weight = 6;
    NewItem->eItemType = EItemType::Armor;

    this->AddItemData(NewItem);

    this->SaveAllItemDataToJson(FilePath);
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemData Save"));
    */

    FString FilePath = TEXT("TestitemData.json");
    this->LoadAllItemDataFromJson(FilePath);
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ItemData Load"));
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
        JsonObject->SetNumberField(TEXT("ItemType"), (int32)ItemData->eItemType);

        JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JsonArray, Writer))
    {
        FString CurrentFilePath = FPaths::ProjectSavedDir() + TEXT("Item/Data/") + FilePath;

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
                    UItemData* LoadedItemData = NewObject<UItemData>();

                    LoadedItemData->name = JsonObject->GetStringField(TEXT("ItemName"));
                    LoadedItemData->description = JsonObject->GetStringField(TEXT("ItemDescription"));
                    LoadedItemData->index = JsonObject->GetNumberField(TEXT("ItemIndex"));
                    LoadedItemData->price = JsonObject->GetNumberField(TEXT("ItemPrice"));
                    LoadedItemData->width = JsonObject->GetNumberField(TEXT("ItemWidth"));
                    LoadedItemData->height = JsonObject->GetNumberField(TEXT("ItemHeight"));
                    LoadedItemData->weight = JsonObject->GetNumberField(TEXT("ItemWeight"));
                    LoadedItemData->eItemType = (EItemType)JsonObject->GetNumberField(TEXT("ItemType"));

                    ItemDataList.Add(LoadedItemData);
                }
            }
        }
    }
}
