// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractPanel.h"
#include "../Framework/PlayerCharacterController.h"

void UItemInteractPanel::NativeConstruct()
{
	Information->OnClicked.AddDynamic(this, &UItemInteractPanel::ShowInformationPanel);
	Use->OnClicked.AddDynamic(this, &UItemInteractPanel::UseItem);
	Trash->OnClicked.AddDynamic(this, &UItemInteractPanel::TrashItem);
}

void UItemInteractPanel::ShowInformationPanel()
{
	if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	SetVisibility(ESlateVisibility::Hidden);
	PlayerController->ItemInfoUI->SetVisibility(ESlateVisibility::Visible);
	PlayerController->ItemInfoUI->SettingItem(PlayerController->InteractItem);
}

void UItemInteractPanel::UseItem()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	SetVisibility(ESlateVisibility::Hidden);

}

void UItemInteractPanel::TrashItem()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	SetVisibility(ESlateVisibility::Hidden);

}
