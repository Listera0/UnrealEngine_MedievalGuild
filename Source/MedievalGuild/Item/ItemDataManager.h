#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.h"

#include "ItemDataManager.generated.h"


UCLASS()
class MEDIEVALGUILD_API UItemDataManager : public UObject
{
	GENERATED_BODY()

public:
	UItemDataManager();

public:
	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	static UItemDataManager* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void AddItemData(UItemData* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void SaveAllItemDataToJson(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	void LoadAllItemDataFromJson(const FString& FilePath);

	UItemData* FindItemData(int ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	TArray<UItemData*> GetItemDataList() const { return ItemDataList; }

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UStaticMesh* GetMeshForItem(const UItemData* item);

	UFUNCTION(BlueprintCallable, Category = "Item Data Manager")
	UMaterialInterface* GetMaterialForItem(const UItemData* item);

private:
	static UItemDataManager* Instance;

	UPROPERTY()
	TArray<UItemData*> ItemDataList;

	FString CurrentFilePath = FPaths::ProjectContentDir() + TEXT("Data/Item/Data/");
};
