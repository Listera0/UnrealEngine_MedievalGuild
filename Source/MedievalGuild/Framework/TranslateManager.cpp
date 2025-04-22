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

	if (PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	SetLanguageOption();
	SetSelectLanguage();
}

void ATranslateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATranslateManager::SetLanguageOption()
{
	IFileManager& FileManager = IFileManager::Get();
	FString DirectoryPath = FPaths::ProjectContentDir() + TEXT("Data/Language/");
	TArray<FString> FileNames;
	FileManager.FindFiles(FileNames, *DirectoryPath, TEXT("json"));
	for (const FString& FileName : FileNames) { TranslateLanguages.Add(FName(*FPaths::GetBaseFilename(FileName))); }
}

void ATranslateManager::SetSelectLanguage()
{
	FString FilePath = FPaths::ProjectContentDir() + FString::Printf(TEXT("Data/Language/%s.json"), *TranslateLanguages[SelectLanguageIndex].ToString());
	FString JsonStr;

	if (FFileHelper::LoadFileToString(JsonStr, *FilePath)) {
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid()) {
			TranslateData.Empty();

			for (const auto& Pair : JsonObject->Values) {
				FString Key = Pair.Key;
				FString Value;

				if (Pair.Value->TryGetString(Value)) {
					TranslateData.Add(Key, Value);
				}
			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Cannot read json file"));
	}
}

FText ATranslateManager::TranslateTexts(FText text)
{
	const FString* Found = TranslateData.Find(text.ToString());
	if (Found) { return FText::FromString(*Found); }

	return text;
}

