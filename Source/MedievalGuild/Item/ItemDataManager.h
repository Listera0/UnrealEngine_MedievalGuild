#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.h"
#include "Recipe/ItemRecipe.h"

#include "ItemDataManager.generated.h"


UCLASS()
class MEDIEVALGUILD_API UItemDataManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	static UItemDataManager* GetInstance();
	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void ClearUp();

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void AddItemData(UItemData* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void AddItemRecipe(UItemRecipe* ItemRecipe);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void SaveAllItemDataToJson();

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void LoadAllItemDataFromJson(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void SaveAllItemRecipeToJson();

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void LoadAllItemRecipeFromJson(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UItemData* FindItemData(int ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	TArray<UItemRecipe*> FindItemRecipe(int ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	TArray<UItemData*> GetItemDataList() const { return ItemDataList; }

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	TArray<UItemRecipe*> GetItemRecipeList() const { return ItemRecipeList; }

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UStaticMesh* GetMeshForItem(const UItemData* item);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UMaterialInterface* GetMaterialForItem(const UItemData* item);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UTexture2D* Get2DSpriteForItem(const UItemData* item);

private:
	static UItemDataManager* Instance;

	UPROPERTY()
	TArray<UItemData*> ItemDataList;

	UPROPERTY()
	TArray<UItemRecipe*> ItemRecipeList;

	FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Item/Data/");

	FString CurrentRecipeFilePath = FPaths::ProjectContentDir() + TEXT("Data/Item/Recipe/");
};
