// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionPanel.h"
#include "GameFramework/GameUserSettings.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/TranslateManager.h"
#include "../Framework/PlayerSettingSave.h"
#include "../Character/PlayerCharacter.h"

void UOptionPanel::InitMainScreenSetting()
{
	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	for (FName lan : PlayerController->TSManager->TranslateLanguages) { LanguageBox->AddOption(lan.ToString()); }
	LanguageBox->SetSelectedOption("en");
	
	LanguageBox->OnSelectionChanged.AddDynamic(this, &UOptionPanel::OnChangeLanguage);
	SensitiveSlider->OnValueChanged.AddDynamic(this, &UOptionPanel::OnChangeSensitive);
	FieldOfViewSlider->OnValueChanged.AddDynamic(this, &UOptionPanel::OnChangeFOV);
	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UOptionPanel::OnChangeFullScreen);
	ResetSaveDataButton->OnClicked.AddDynamic(this, &UOptionPanel::ResetSaveData);
	CancelButton->OnClicked.AddDynamic(this, &UOptionPanel::CancelOptionPanel);

	LoadPlayerSetting();
}

void UOptionPanel::MainLanguageSetting()
{
	ATranslateManager* TSManager = PlayerController->TSManager;
	PlayerController->MainMenuUI->StartGameText->SetText(TSManager->TranslateTexts(FText::FromString("Load")));
	PlayerController->MainMenuUI->NewGameText->SetText(TSManager->TranslateTexts(FText::FromString("New")));
	PlayerController->MainMenuUI->OptionText->SetText(TSManager->TranslateTexts(FText::FromString("Option")));
	PlayerController->MainMenuUI->ExitGameText->SetText(TSManager->TranslateTexts(FText::FromString("Exit")));
}

void UOptionPanel::OptionLanguageSetting()
{
	ATranslateManager* TSManager = PlayerController->TSManager;
	W_Value->SetText(TSManager->TranslateTexts(FText::FromString("Front Move")));
	A_Value->SetText(TSManager->TranslateTexts(FText::FromString("Left Move")));
	S_Value->SetText(TSManager->TranslateTexts(FText::FromString("Back Move")));
	D_Value->SetText(TSManager->TranslateTexts(FText::FromString("Right Move")));
	Tab_Value->SetText(TSManager->TranslateTexts(FText::FromString("Menu")));
	Left_Value->SetText(TSManager->TranslateTexts(FText::FromString("Fast Attack")));
	Right_Value->SetText(TSManager->TranslateTexts(FText::FromString("Slow Attack")));
	LanguageText->SetText(TSManager->TranslateTexts(FText::FromString("Language")));
	SensitiveText->SetText(TSManager->TranslateTexts(FText::FromString("Sensitive")));
	FieldOfViewText->SetText(TSManager->TranslateTexts(FText::FromString("FOV")));
	FullScreenText->SetText(TSManager->TranslateTexts(FText::FromString("FullScreen")));
}

void UOptionPanel::SavePlayerSetting()
{
	UPlayerSettingSave* SaveGameInstance = Cast<UPlayerSettingSave>(UGameplayStatics::CreateSaveGameObject(UPlayerSettingSave::StaticClass()));

	if (SaveGameInstance)
	{
		// Save Data
		SaveGameInstance->SavePlayerSetting(LanguageBox->GetSelectedIndex(), (int)(SensitiveSlider->GetValue()), (int)(FieldOfViewSlider->GetValue()),
			FullScreenCheckBox->IsChecked());

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSettingData"), 0);
	}
}

void UOptionPanel::LoadPlayerSetting()
{
	UPlayerSettingSave* LoadGameInstance = Cast<UPlayerSettingSave>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSettingData"), 0));

	if (!LoadGameInstance) return;

	// Load Data
	int lan; int sen; int fov; bool fulls;
	LoadGameInstance->LoadPlayerSetting(lan, sen, fov, fulls);

	LanguageBox->SetSelectedIndex(lan);
	SensitiveSlider->SetValue(sen);
	FieldOfViewSlider->SetValue(fov);
	FullScreenCheckBox->SetIsChecked(fulls);
}

void UOptionPanel::OnChangeLanguage(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	PlayerController->TSManager->SelectLanguageIndex = LanguageBox->GetSelectedIndex();
	PlayerController->TSManager->SetSelectLanguage();

	OptionLanguageSetting();
	PlayerController->StaticUITranslate();

	SavePlayerSetting();
}

void UOptionPanel::OnChangeSensitive(float Value)
{
	SensitiveValue->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Value)));
	PlayerController->CameraSensitive = Value * 0.01f;
	SavePlayerSetting();
}

void UOptionPanel::OnChangeFOV(float Value)
{
	FieldOfViewValue->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Value)));
	PlayerController->PlayerCharacter->PlayerCamera->SetFieldOfView(Value);
	SavePlayerSetting();
}

void UOptionPanel::OnChangeFullScreen(bool bIsChecked)
{
	bIsChecked ? GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen) : GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->ApplySettings(true);
	SavePlayerSetting();
}

void UOptionPanel::ResetSaveData()
{
	PlayerController->PlayerData->RemoveSave();
	PlayerController->MainMenuUI->MainButtonSetting();
}

void UOptionPanel::CancelOptionPanel()
{
	SetVisibility(ESlateVisibility::Hidden);
}
