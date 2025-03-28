// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractPanel.h"
#include "../Framework/PlayerCharacterController.h"

void UItemInteractPanel::NativeConstruct()
{
	Information->OnClicked.AddDynamic(this, &UItemInteractPanel::ShowInformationPanel);
	Equip->OnClicked.AddDynamic(this, &UItemInteractPanel::EquipItem);
	Use->OnClicked.AddDynamic(this, &UItemInteractPanel::UseItem);
	Trash->OnClicked.AddDynamic(this, &UItemInteractPanel::TrashItem);
}

void UItemInteractPanel::ShowPanelSetting(FVector2D Scale)
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	int ButtonCount = 0;
	SetVisibility(ESlateVisibility::Visible);

	Information->SetVisibility(ESlateVisibility::Visible);

	if (PlayerController->PlayerData->GetEquipmentIndex(PlayerController->ItemInteractUI->InteractItem->ItemData->eItemType) != -1) {
		Equip->SetVisibility(ESlateVisibility::Visible);
		ButtonCount++;
	}
	else {
		Equip->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PlayerController->ItemInteractUI->InteractItem->ItemData->eItemType == EItemType::Consumeable) {
		Use->SetVisibility(ESlateVisibility::Visible);
		ButtonCount++;
	}
	else {
		Use->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PlayerController->InteractObj && PlayerController->InteractObj->ActorHasTag("Merchant")) {
		Trash->SetVisibility(ESlateVisibility::Collapsed);
	}
	else {
		Trash->SetVisibility(ESlateVisibility::Visible);
		ButtonCount++;
	}

	ButtonCount += 1;

	PlayerController->ItemInteractUI->SetDesiredSizeInViewport(FVector2D(150.0f, 40.0f * (float)(ButtonCount)) * Scale);
}

void UItemInteractPanel::ShowInformationPanel()
{
	SetVisibility(ESlateVisibility::Hidden);
	PlayerController->ItemInfoUI->SetVisibility(ESlateVisibility::Visible);
	PlayerController->ItemInfoUI->SettingItem(PlayerController->ItemInteractUI->InteractItem);
}

void UItemInteractPanel::EquipItem()
{

	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInteractPanel::UseItem()
{

	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInteractPanel::TrashItem()
{
	PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(InteractContainer), InteractItem->SlotIndex, true);
	PlayerController->GetTargetContainer(InteractContainer)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(InteractContainer));

	SetVisibility(ESlateVisibility::Hidden);
}
