// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "OptionPanel.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API UOptionPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitMainScreenSetting();

	void SavePlayerSetting();
	void LoadPlayerSetting();

	UFUNCTION()
	void OnChangeLanguage(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void OnChangeSensitive(float Value);
	UFUNCTION()
	void OnChangeFOV(float Value);
	UFUNCTION()
	void OnChangeFullScreen(bool bIsChecked);
	UFUNCTION()
	void ResetSaveData();
	UFUNCTION()
	void CancelOptionPanel();

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* LanguageBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	USlider* SensitiveSlider = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SensitiveValue = nullptr;
	UPROPERTY(meta = (BindWidget))
	USlider* FieldOfViewSlider = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FieldOfViewValue = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCheckBox* FullScreenCheckBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* W_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* A_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* S_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* D_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tab_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Left_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Right_Value = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LanguageText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SensitiveText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FieldOfViewText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FullScreenText = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ResetSaveDataButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResetSaveDataText = nullptr;

public:
	class APlayerCharacterController* PlayerController = nullptr;

	TArray<FString> LanguageOptions;
};
