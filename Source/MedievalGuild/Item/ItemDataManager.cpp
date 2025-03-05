#include "ItemDataManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

UItemDataManager* UItemDataManager::Instance = nullptr;

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
        ItemDataList.Add(ItemData);
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
        JsonObject->SetNumberField(TEXT("ItemPrice"), ItemData->price);
        JsonObject->SetNumberField(TEXT("ItemIndex"), ItemData->index);
        JsonObject->SetNumberField(TEXT("ItemCount"), ItemData->count);
        JsonObject->SetNumberField(TEXT("ItemHeight"), ItemData->height);
        JsonObject->SetNumberField(TEXT("ItemWeight"), ItemData->weight);
        JsonObject->SetNumberField(TEXT("ItemType"), (int32)ItemData->eItemType);

        JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JsonArray, Writer))
    {
        FFileHelper::SaveStringToFile(OutputString, *FilePath);
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
                    LoadedItemData->price = JsonObject->GetNumberField(TEXT("ItemPrice"));
                    LoadedItemData->index = JsonObject->GetNumberField(TEXT("ItemIndex"));
                    LoadedItemData->count = JsonObject->GetNumberField(TEXT("ItemCount"));
                    LoadedItemData->height = JsonObject->GetNumberField(TEXT("ItemHeight"));
                    LoadedItemData->weight = JsonObject->GetNumberField(TEXT("ItemWeight"));
                    LoadedItemData->eItemType = (EItemType)JsonObject->GetNumberField(TEXT("ItemType"));

                    ItemDataList.Add(LoadedItemData);
                }
            }
        }
    }
}
