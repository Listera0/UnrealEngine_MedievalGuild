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

    // 아이템 넓이
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int width;

    // 아이템 높이
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int height;

    // 아이템 무게
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int weight;

    // 스택 가능 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    bool bStackable;

    // 최대 스택 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int maxStack;
};
