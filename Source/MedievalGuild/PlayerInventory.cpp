// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"


void UPlayerInventory::NativeConstruct()
{
	MakeInventory(2, 2);
}

void UPlayerInventory::MakeInventory(int col, int row)
{
	if (!SlotGridPanel)
		return;


	UButton* newButton = NewObject<UButton>(this);
	UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newButton, 1, 1);


	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			UButton* newButton = NewObject<UButton>(this);
			UUniformGridSlot* gridSlot = SlotGridPanel->AddChildToUniformGrid(newButton, i, j);
		}
	}
}
