// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Character/PlayerCharacter.h"

void UEquipmentWidget::InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
									TSubclassOf<UUserWidget> gearWidget, TSubclassOf<UUserWidget> itemSlotImgClass)
{
	ItemSlotClass = itemSlotClass;
	ItemSlotImgClass = itemSlotImgClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	GearWidget = gearWidget;

	// Helmet
	Widget_Helmet = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Helmet->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Helmet, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Helmet = HelmetSlot->AddChildToCanvas(Widget_Helmet);
	Slot_Helmet->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Cloth
	Widget_Cloth = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Cloth->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Cloth, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Cloth = ClothSlot->AddChildToCanvas(Widget_Cloth);
	Slot_Cloth->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Shoes
	Widget_Shoes = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Shoes->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Shoes, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Shoes = ShoesSlot->AddChildToCanvas(Widget_Shoes);
	Slot_Shoes->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Bag
	Widget_Bag = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Bag->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Bag, FVector2D(3, 3));
	UCanvasPanelSlot* Slot_Bag = BagSlot->AddChildToCanvas(Widget_Bag);
	Slot_Bag->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Weapon
	Widget_Weapon = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Weapon->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Weapon, FVector2D(3, 1));
	UCanvasPanelSlot* Slot_Weapon = WeaponSlot->AddChildToCanvas(Widget_Weapon);
	Slot_Weapon->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
}

void UEquipmentWidget::ShowContainer()
{
	if (!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	Widget_Helmet->ShowContainer(PlayerController->PlayerData->PlayerEquipment[0]);
	Widget_Cloth->ShowContainer(PlayerController->PlayerData->PlayerEquipment[1]);
	Widget_Shoes->ShowContainer(PlayerController->PlayerData->PlayerEquipment[2]);
	Widget_Bag->ShowContainer(PlayerController->PlayerData->PlayerEquipment[3]);
	Widget_Weapon->ShowContainer(PlayerController->PlayerData->PlayerEquipment[4]);

	UpdateWeapon();
	ShowContainerInfo();
}

void UEquipmentWidget::ShowContainerInfo()
{
	if(!PlayerController) PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	HealthValue->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)(PlayerController->PlayerData->PlayerHealth))));
	SteminaValue->SetText(FText::FromString(FString::Printf(TEXT("%d"), (int)(PlayerController->PlayerData->PlayerStemina))));

	float totalWeight = 0;
	float equipmentWeight = 0.0f;
	for (int i = 0; i < PlayerController->PlayerData->PlayerEquipment.Num(); i++){
		if (PlayerController->PlayerData->PlayerEquipment[i]) {
			equipmentWeight += PlayerController->PlayerData->PlayerEquipment[i]->ItemData->weight;
		}
	}

	float itemWeight = 0.0f;
	for (FInventoryData* data : PlayerController->PlayerData->PlayerInventory) {
		itemWeight += (float)(data->ItemData->weight * data->ItemCount);
	}

	totalWeight = equipmentWeight + itemWeight;
	WeightValue->SetText(FText::FromString(FString::Printf(TEXT("%0.1f"), totalWeight)));
}

void UEquipmentWidget::UpdateWeapon()
{
	if (PlayerController->PlayerData->PlayerEquipment[4]) { PlayerController->PlayerCharacter->SetPlayerWeapon(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Weapon)[4]->ItemData->index); }
	else { PlayerController->PlayerCharacter->SetPlayerWeapon(-1); }
}
