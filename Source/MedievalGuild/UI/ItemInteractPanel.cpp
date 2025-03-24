// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractPanel.h"

void UItemInteractPanel::NativeConstruct()
{
	Information->OnClicked.AddDynamic(this, &UItemInteractPanel::ShowInformationPanel);
	Use->OnClicked.AddDynamic(this, &UItemInteractPanel::UseItem);
	Trash->OnClicked.AddDynamic(this, &UItemInteractPanel::TrashItem);
}

void UItemInteractPanel::ShowInformationPanel()
{
}

void UItemInteractPanel::UseItem()
{
}

void UItemInteractPanel::TrashItem()
{
}
