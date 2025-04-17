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
	SaveGame->OnClicked.AddDynamic(this, &UOptionMenu::OnClickSaveGame);
	LoadGame->OnClicked.AddDynamic(this, &UOptionMenu::OnClickLoadGame);
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
	UQuestManager::GetInstance()->SaveAllQuestDataToJson();
}

void UOptionMenu::OnClickSaveGame()
{
	PlayerController->PlayerData->SaveGame();
}

void UOptionMenu::OnClickLoadGame()
{
	PlayerController->PlayerData->LoadGame();
}

void UOptionMenu::OnClickExitGame()
{
	Cast<AGameManager>(GetWorld()->GetAuthGameMode())->GameEndSequence();
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
