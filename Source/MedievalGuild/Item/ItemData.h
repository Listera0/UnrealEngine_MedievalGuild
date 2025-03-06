#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EItemType.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType)
class MEDIEVALGUILD_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	// 아이템 데이터를 JSON으로 저장하는 함수
	UFUNCTION(BlueprintCallable, Category = "Item Data")
	void SaveItemDataToJson(const FString& FilePath);

	// JSON 파일에서 아이템 데이터를 불러오는 함수
	UFUNCTION(BlueprintCallable, Category = "Item Data")
	static UItemData* LoadItemDataFromJson(const FString& FilePath);

	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemType eItemType;

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString name;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FString description;

	// 아이템 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	float price;

	// 아이템 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int index;

	// 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int count;

	// 아이템 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int height;

	// 아이템 무게
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int weight;
};
