// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Quest/QuestManager.h"
#include "../Framework/GameManager.h"

void UOptionMenu::OptionMenuInitSetting()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	ShowInventory->OnClicked.AddDynamic(this, &UOptionMenu::OnClickShowInventory);
	ShowQuest->OnClicked.AddDynamic(this, &UOptionMenu::OnClickShowQuest);
	ShowOption->OnClicked.AddDynamic(this, &UOptionMenu::OnClickShowOption);
	ExitGame->OnClicked.AddDynamic(this, &UOptionMenu::OnClickExitGame);
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
	PlayerController->OptionPanelUI->SetVisibility(ESlateVisibility::Visible);
}

void UOptionMenu::OnClickExitGame()
{
	if(PlayerController->CurrentPlayerLocation != "Tutorial") Cast<AGameManager>(GetWorld()->GetAuthGameMode())->GameEndSequence();
	PlayerController->AllUIHidden();
	PlayerController->ScreenUI->AllTextClose();
	PlayerController->MainMenuUI->MainButtonSetting();
	PlayerController->MainMenuUI->InitMainScreenSetting();

	//UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
