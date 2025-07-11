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
        FString FilePath = TEXT("TestitemData.json");
        Instance->LoadAllItemDataFromJson(FilePath);

		FilePath = TEXT("ItemRecipe.json");
		Instance->LoadAllItemRecipeFromJson(FilePath);
    }
    return Instance;
}

void UItemDataManager::ClearUp()
{
    if (Instance)
    {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
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

void UItemDataManager::AddItemRecipe(UItemRecipe* ItemRecipe)
{
    if (ItemRecipe)
    {
        ItemRecipeList.Add(ItemRecipe);
    }
}

void UItemDataManager::SaveAllItemDataToJson()
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

        JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
    }

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

    if (FJsonSerializer::Serialize(JsonArray, Writer))
    {
        FString Path = CurrentFilePath + TEXT("TestitemData.json");

        FFileHelper::SaveStringToFile(OutputString, *Path, FFileHelper::EEncodingOptions::ForceUTF8);
    }
}


void UItemDataManager::LoadAllItemDataFromJson(const FString& FilePath)
{
    FString FileContents;
    FString Path = CurrentFilePath + FilePath;

    if (FFileHelper::LoadFileToString(FileContents, *Path))
    {
        TArray<TSharedPtr<FJsonValue>> JsonArray;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);

        if (FJsonSerializer::Deserialize(Reader, JsonArray))
        {
            ItemDataList.Empty();
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

                    ItemDataList.Add(LoadedItemData);
                }
            }
        }
    }
}

void UItemDataManager::SaveAllItemRecipeToJson()
{
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (UItemRecipe* ItemRecipe : ItemRecipeList)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		JsonObject->SetNumberField(TEXT("MakeItemIndex"), ItemRecipe->MakeItemIndex);
		JsonObject->SetNumberField(TEXT("MakeItemAmount"), ItemRecipe->MakeItemAmount);

		TArray<TSharedPtr<FJsonValue>> IngredientsIndexArray;
		for (int Index : ItemRecipe->IngredientsIndex)
		{
			IngredientsIndexArray.Add(MakeShareable(new FJsonValueNumber(Index)));
		}
		JsonObject->SetArrayField(TEXT("IngredientsIndex"), IngredientsIndexArray);

		TArray<TSharedPtr<FJsonValue>> IngredientsAmountArray;
		for (int Amount : ItemRecipe->IngredientsAmount)
		{
			IngredientsAmountArray.Add(MakeShareable(new FJsonValueNumber(Amount)));
		}
		JsonObject->SetArrayField(TEXT("IngredientsAmount"), IngredientsAmountArray);
		JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
	}
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	if (FJsonSerializer::Serialize(JsonArray, Writer))
	{
		FString Path = CurrentRecipeFilePath + TEXT("ItemRecipe.json");
		FFileHelper::SaveStringToFile(OutputString, *Path, FFileHelper::EEncodingOptions::ForceUTF8);
	}
}

void UItemDataManager::LoadAllItemRecipeFromJson(const FString& FilePath)
{
	FString FileContents;
	FString Path = CurrentRecipeFilePath + FilePath;

    bool IsNotFoundItem = false;

	if (FFileHelper::LoadFileToString(FileContents, *Path))
	{
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			ItemRecipeList.Empty();
			for (TSharedPtr<FJsonValue> JsonValue : JsonArray)
			{
				IsNotFoundItem = false;
				if (JsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();
					UItemRecipe* LoadedItemRecipe = NewObject<UItemRecipe>();
					LoadedItemRecipe->MakeItemIndex = JsonObject->GetNumberField(TEXT("MakeItemIndex"));
					LoadedItemRecipe->MakeItemAmount = JsonObject->GetNumberField(TEXT("MakeItemAmount"));

                    if (!FindItemData(LoadedItemRecipe->MakeItemIndex))
                        continue;

					const TArray<TSharedPtr<FJsonValue>>& IngredientsIndexArray = JsonObject->GetArrayField(TEXT("IngredientsIndex"));
					for (const TSharedPtr<FJsonValue>& Value : IngredientsIndexArray)
					{
                        if (!FindItemData(Value->AsNumber()))
                        {
							IsNotFoundItem = true;
                            break;
                        }
						LoadedItemRecipe->IngredientsIndex.Add(Value->AsNumber());
					}

                    if (IsNotFoundItem)
                        continue;

					const TArray<TSharedPtr<FJsonValue>>& IngredientsAmountArray = JsonObject->GetArrayField(TEXT("IngredientsAmount"));
					for (const TSharedPtr<FJsonValue>& Value : IngredientsAmountArray)
					{
						LoadedItemRecipe->IngredientsAmount.Add(Value->AsNumber());
					}
					ItemRecipeList.Add(LoadedItemRecipe);
				}
			}
		}
	}
}

UItemData* UItemDataManager::FindItemData(int ItemIndex)
{
    UItemData* FindItem = nullptr;
    for (UItemData* ItemData : ItemDataList)
    {
        if (ItemData->index == ItemIndex)
        {
            FindItem = ItemData;
            break;
        }
    }
    return FindItem;
}

TArray<UItemRecipe*> UItemDataManager::FindItemRecipe(int ItemIndex)
{
	TArray<UItemRecipe*> FindItemRecipeList;
	for (UItemRecipe* ItemRecipe : ItemRecipeList)
	{
		if (ItemRecipe->MakeItemIndex == ItemIndex)
		{
			FindItemRecipeList.Add(ItemRecipe);
		}
	}
	return FindItemRecipeList;
}

UStaticMesh* UItemDataManager::GetMeshForItem(const UItemData* item)
{
    if (!item)
        return nullptr;

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
    if (!item)
        return nullptr;

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

UTexture2D* UItemDataManager::Get2DSpriteForItem(const UItemData* item)
{
    if (!item)
        return nullptr;

    FString TextureReference = FString::Printf(TEXT("%d_%s"), item->index, *item->name);
    FString TexturePath = FString::Printf(TEXT("/Game/Data/Item/Texture/%s"), *TextureReference);

    UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *TexturePath);

    if (Texture)
    {
        return Texture;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Texture: %s"), *TexturePath);
        return nullptr;
    }
}
