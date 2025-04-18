// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslateManager.h"
#include "../Framework/PlayerCharacterController.h"

ATranslateManager::ATranslateManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATranslateManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATranslateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATranslateManager::TranslateTexts()
{
	if (PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	//PlayerController->InventoryUI->Widget_CraftInventory->
}

void ATranslateManager::TranslateTexts(FText text)
{
	if (PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());


	FString FilePath = FPaths::ProjectContentDir() + FString::Printf(TEXT("Data/Language/%s.json"), *TranslateLanguages[SelectLanguageIndex].ToString());
	FString JsonStr;

	if (FFileHelper::LoadFileToString(JsonStr, *FilePath)) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			FString Name = JsonObject->GetStringField("Name");
			int32 Value = JsonObject->GetIntegerField("Value");

			UE_LOG(LogTemp, Warning, TEXT("Name: %s, Value: %d"), *Name, Value);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Json 파일 읽기 실패: %s"), *FilePath);
	}
}

