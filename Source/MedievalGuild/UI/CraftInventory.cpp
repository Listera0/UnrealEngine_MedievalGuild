// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftInventory.h"
#include "Kismet/GameplayStatics.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Framework/TranslateManager.h"
#include "../Item/ItemDataManager.h"

void UCraftInventory::ShowContainer(TArray<FInventoryData*>& data)
{
	Super::ShowContainer(data);

	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	CraftTableName->SetText(PlayerController->TSManager->TranslateTexts(FText::FromName(PlayerController->InteractObj->ObjectName)));
}

void UCraftInventory::CraftInventoryInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size)
{
	ContainerInitSetting(InitWidgetClass[0], InitWidgetClass[1], InitWidgetClass[2], InitWidgetClass[3], category, size);
	GetCraftItemList();
}

void UCraftInventory::GetCraftItemList()
{
	TArray<AActor*> resultArray;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AInteractObject_Base::StaticClass(), "Anvil", resultArray);
	AInteractObject_Base* anvilObject = Cast<AInteractObject_Base>(resultArray[0]);
	TArray<UItemRecipe*> itemRecipes = UItemDataManager::GetInstance()->GetItemRecipeList();
	for (UItemRecipe* recipe : itemRecipes) {
		anvilObject->ContainerInventory.Add(new FInventoryData(FVector2D(-1.0f), UItemDataManager::GetInstance()->FindItemData(recipe->MakeItemIndex), recipe->MakeItemAmount));
	}
	anvilObject->bIsInit = false;
}
