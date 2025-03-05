#include "ItemData.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"


void UItemData::SaveItemDataToJson(const FString& FilePath)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());


	JsonObject->SetStringField("ItemName", name);
	JsonObject->SetStringField("ItemDescription", description);
	JsonObject->SetNumberField("ItemPrice", price);
	JsonObject->SetNumberField("ItemIndex", index);
	JsonObject->SetNumberField("ItemCount", count);
	JsonObject->SetNumberField("ItemHeight", height);
	JsonObject->SetNumberField("ItemWeight", weight);
	JsonObject->SetNumberField("ItemType", (int32)eItemType);


	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);


	FFileHelper::SaveStringToFile(OutputString, *FilePath);
}


UItemData* UItemData::LoadItemDataFromJson(const FString& FilePath)
{
    FString FileContents;
    if (FFileHelper::LoadFileToString(FileContents, *FilePath))
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);


        if (FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            UItemData* LoadedItemData = NewObject<UItemData>();


            LoadedItemData->name = JsonObject->GetStringField(TEXT("ItemName"));
            LoadedItemData->description = JsonObject->GetStringField(TEXT("ItemDescription"));
            LoadedItemData->price = JsonObject->GetNumberField(TEXT("ItemPrice"));
            LoadedItemData->index = JsonObject->GetNumberField(TEXT("ItemIndex"));
            LoadedItemData->count = JsonObject->GetNumberField(TEXT("ItemCount"));
            LoadedItemData->height = JsonObject->GetNumberField(TEXT("ItemHeight"));
            LoadedItemData->weight = JsonObject->GetNumberField(TEXT("ItemWeight"));
            LoadedItemData->eItemType = (EItemType)JsonObject->GetNumberField(TEXT("ItemType"));

            return LoadedItemData;
        }
    }

    return nullptr;
}
