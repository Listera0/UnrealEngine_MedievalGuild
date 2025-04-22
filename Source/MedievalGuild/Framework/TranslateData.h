#pragma once

#include "CoreMinimal.h"
#include "TranslateData.generated.h"

USTRUCT(BlueprintType)
struct FTranslateData
{
	GENERATED_BODY()
	
	FTranslateData() { TextData = ""; TransData = ""; };
	FTranslateData(FString text, FString trans) { TextData = text; TransData = trans; };

public:
	UPROPERTY(BlueprintReadWrite)
	FString TextData;
	UPROPERTY(BlueprintReadWrite)
	FString TransData;
};