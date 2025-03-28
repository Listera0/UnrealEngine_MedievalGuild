// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionMenu.h"
#include "../Framework/PlayerCharacterController.h"

void UOptionMenu::OptionMenuInitSetting()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	ShowInventory->OnClicked.AddDynamic(this, &UOptionMenu::OnClickShowInventory);
	ShowQuest->OnClicked.AddDynamic(this, &UOptionMenu::OnClickShowQuest);
}

void UOptionMenu::OnClickShowInventory()
{
	PlayerController->InventoryUI->PanelVisibleSetting(0);
}

void UOptionMenu::OnClickShowQuest()
{
	PlayerController->InventoryUI->PanelVisibleSetting(5);
}

void UOptionMenu::OnClickShowOption()
{
}

void UOptionMenu::OnClickExitGame()
{
}
