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

	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	SetLanguageOption();
}

void ATranslateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATranslateManager::TranslateManagerInitSetting()
{
	
}

void ATranslateManager::SetStaticUITranslate()
{
	PlayerController->MainMenuUI->StartGameText->SetText(TranslateTexts(FText::FromString("Load")));
	PlayerController->MainMenuUI->NewGameText->SetText(TranslateTexts(FText::FromString("New")));
	PlayerController->MainMenuUI->OptionText->SetText(TranslateTexts(FText::FromString("Option")));
	PlayerController->MainMenuUI->ExitGameText->SetText(TranslateTexts(FText::FromString("Exit")));

	PlayerController->OptionPanelUI->W_Value->SetText(TranslateTexts(FText::FromString("Front Move")));
	PlayerController->OptionPanelUI->A_Value->SetText(TranslateTexts(FText::FromString("Left Move")));
	PlayerController->OptionPanelUI->S_Value->SetText(TranslateTexts(FText::FromString("Back Move")));
	PlayerController->OptionPanelUI->D_Value->SetText(TranslateTexts(FText::FromString("Right Move")));
	PlayerController->OptionPanelUI->Tab_Value->SetText(TranslateTexts(FText::FromString("Menu")));
	PlayerController->OptionPanelUI->Left_Value->SetText(TranslateTexts(FText::FromString("Fast Attack")));
	PlayerController->OptionPanelUI->Right_Value->SetText(TranslateTexts(FText::FromString("Slow Attack")));
	PlayerController->OptionPanelUI->LanguageText->SetText(TranslateTexts(FText::FromString("Language")));
	PlayerController->OptionPanelUI->SensitiveText->SetText(TranslateTexts(FText::FromString("Sensitive")));
	PlayerController->OptionPanelUI->FieldOfViewText->SetText(TranslateTexts(FText::FromString("FOV")));
	PlayerController->OptionPanelUI->FullScreenText->SetText(TranslateTexts(FText::FromString("FullScreen")));

	PlayerController->InventoryUI->Widget_CraftRequire->RequireText->SetText(TranslateTexts(FText::FromString("Require Item List")));
	PlayerController->InventoryUI->Widget_CraftRequire->CraftText->SetText(TranslateTexts(FText::FromString("Craft")));

	PlayerController->InventoryUI->Widget_QuestPlayerPanel->QuestText->SetText(TranslateTexts(FText::FromString("Quest List")));

	PlayerController->InventoryUI->Widget_OptionMenu->InvText->SetText(TranslateTexts(FText::FromString("Inventory")));
	PlayerController->InventoryUI->Widget_OptionMenu->QuestText->SetText(TranslateTexts(FText::FromString("Quest")));
	PlayerController->InventoryUI->Widget_OptionMenu->OptionText->SetText(TranslateTexts(FText::FromString("Option")));
	PlayerController->InventoryUI->Widget_OptionMenu->ExitText->SetText(TranslateTexts(FText::FromString("Exit")));

	PlayerController->InventoryUI->Widget_StageMap->LibraryText->SetText(TranslateTexts(FText::FromString("Library")));
	PlayerController->InventoryUI->Widget_StageMap->LockText1->SetText(TranslateTexts(FText::FromString("Lock")));
	PlayerController->InventoryUI->Widget_StageMap->LockText2->SetText(TranslateTexts(FText::FromString("Lock")));

	PlayerController->ScreenUI->GetTutorialMessage(0, 0)->SetText(TranslateTexts(FText::FromString("Tutorial - 1 -")));
	PlayerController->ScreenUI->GetTutorialMessage(0, 1)->SetText(TranslateTexts(FText::FromString("WASD -> Move\nMouse Move -> Camera Move")));
	PlayerController->ScreenUI->GetTutorialMessage(0, 2)->SetText(TranslateTexts(FText::FromString("- Go Forward -")));
	
	PlayerController->ScreenUI->GetTutorialMessage(1, 0)->SetText(TranslateTexts(FText::FromString("Tutorial - 2 -")));
	PlayerController->ScreenUI->GetTutorialMessage(1, 1)->SetText(TranslateTexts(FText::FromString("F -> Interact Object, NPC\nDrag -> Move Item")));
	PlayerController->ScreenUI->GetTutorialMessage(1, 2)->SetText(TranslateTexts(FText::FromString("- Pick gem and buy Dagger -")));

	PlayerController->ScreenUI->GetTutorialMessage(2, 0)->SetText(TranslateTexts(FText::FromString("Tutorial - 3 -")));
	PlayerController->ScreenUI->GetTutorialMessage(2, 1)->SetText(TranslateTexts(FText::FromString("Tab -> Menu\nShift + LeftClick -> Move Item")));
	PlayerController->ScreenUI->GetTutorialMessage(2, 2)->SetText(TranslateTexts(FText::FromString("- Equip Dagger -")));

	PlayerController->ScreenUI->GetTutorialMessage(3, 0)->SetText(TranslateTexts(FText::FromString("Tutorial - 4 -")));
	PlayerController->ScreenUI->GetTutorialMessage(3, 1)->SetText(TranslateTexts(FText::FromString("LeftClick -> QuickAttack\nRightClick -> StrongAttack")));
	PlayerController->ScreenUI->GetTutorialMessage(3, 2)->SetText(TranslateTexts(FText::FromString("- Kill Enemy -")));

	PlayerController->ScreenUI->GetTutorialMessage(4, 0)->SetText(TranslateTexts(FText::FromString("Tutorial - 5 -")));
	PlayerController->ScreenUI->GetTutorialMessage(4, 1)->SetText(TranslateTexts(FText::FromString("Stay area for extract")));
	PlayerController->ScreenUI->GetTutorialMessage(4, 2)->SetText(TranslateTexts(FText::FromString("- Extract Area -")));
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

FString ATranslateManager::TranslateTexts(FString text)
{
	const FString* Found = TranslateData.Find(text);
	if (Found) { return *Found; }

	return text;
}

