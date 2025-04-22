// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractPanel.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/TranslateManager.h"
#include "../DataAssets/ItemEffectDataAsset.h"

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
	InformationText->SetText(PlayerController->TSManager->TranslateTexts(FText::FromString("Info")));

	if (PlayerController->PlayerData->GetEquipmentIndex(PlayerController->ItemInteractUI->InteractItem->ItemData->eItemType) != -1) {
		Equip->SetVisibility(ESlateVisibility::Visible);
		EquipText->SetText(PlayerController->TSManager->TranslateTexts(FText::FromString("Equip")));
		ButtonCount++;
	}
	else {
		Equip->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (PlayerController->ItemInteractUI->InteractItem->ItemData->eItemType == EItemType::Consumeable) {
		Use->SetVisibility(ESlateVisibility::Visible);
		UseText->SetText(PlayerController->TSManager->TranslateTexts(FText::FromString("Use")));
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
		TrashText->SetText(PlayerController->TSManager->TranslateTexts(FText::FromString("Trash")));
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
	switch (PlayerController->PlayerData->GetEquipmentIndex(InteractItem->ItemData->eItemType))
	{
		case 0: PlayerController->InventoryUI->Widget_Equipment->Widget_Helmet->MoveItemToSlot(InteractContainer, InteractItem); break;
		case 1: PlayerController->InventoryUI->Widget_Equipment->Widget_Cloth->MoveItemToSlot(InteractContainer, InteractItem); break;
		case 2: PlayerController->InventoryUI->Widget_Equipment->Widget_Shoes->MoveItemToSlot(InteractContainer, InteractItem); break;
		case 3: PlayerController->InventoryUI->Widget_Equipment->Widget_Bag->MoveItemToSlot(InteractContainer, InteractItem); break;
		case 4: PlayerController->InventoryUI->Widget_Equipment->Widget_Weapon->MoveItemToSlot(InteractContainer, InteractItem); break;
		default: break;
	}

	PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInteractPanel::UseItem()
{
	FStringAssetReference spawnRef(FString::Printf(TEXT("/Game/CPP/DataAsset/%d_ItemEffectData"), PlayerController->ItemInteractUI->InteractItem->ItemData->index));
	UItemEffectDataAsset* effectData = Cast<UItemEffectDataAsset>(spawnRef.TryLoad());
	if (effectData) {
		for (int i = 0; i < effectData->ItemTarget.Num(); i++) {
			if (effectData->ItemTarget[i] == EEffectTarget::Health) {
				PlayerController->PlayerData->PlayerHealth += effectData->TargetValue[i];
				PlayerController->InventoryUI->Widget_Equipment->ShowContainer();
			}
		}

		if (InteractItem->ItemCount > 1) { InteractItem->ItemCount--; }
		else { PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(InteractContainer), InteractItem->SlotIndex, true); }
		PlayerController->GetTargetContainer(InteractContainer)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(InteractContainer));
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UItemInteractPanel::TrashItem()
{
	PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(InteractContainer), InteractItem->SlotIndex, true);
	PlayerController->GetTargetContainer(InteractContainer)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(InteractContainer));

	SetVisibility(ESlateVisibility::Hidden);
}
