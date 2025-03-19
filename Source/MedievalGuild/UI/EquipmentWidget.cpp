// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"
#include "../Framework/PlayerCharacterController.h"

void UEquipmentWidget::InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
									TSubclassOf<UUserWidget> gearWidget)
{
	ItemSlotClass = itemSlotClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	GearWidget = gearWidget;

	// Helmet
	Widget_Helmet = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Helmet->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Helmet, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Helmet = HelmetSlot->AddChildToCanvas(Widget_Helmet);
	Slot_Helmet->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Cloth
	Widget_Cloth = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Cloth->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Cloth, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Cloth = ClothSlot->AddChildToCanvas(Widget_Cloth);
	Slot_Cloth->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Shoes
	Widget_Shoes = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Shoes->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Shoes, FVector2D(2, 2));
	UCanvasPanelSlot* Slot_Shoes = ShoesSlot->AddChildToCanvas(Widget_Shoes);
	Slot_Shoes->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Bag
	Widget_Bag = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Bag->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Bag, FVector2D(3, 3));
	UCanvasPanelSlot* Slot_Bag = BagSlot->AddChildToCanvas(Widget_Bag);
	Slot_Bag->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Weapon
	Widget_Weapon = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Weapon->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Weapon, FVector2D(3, 1));
	UCanvasPanelSlot* Slot_Weapon = WeaponSlot->AddChildToCanvas(Widget_Weapon);
	Slot_Weapon->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
}

void UEquipmentWidget::ShowContainer()
{
	APlayerCharacterController* controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

	Widget_Helmet->ShowContainer(controller->PlayerData->PlayerEquipment[0]);
	Widget_Cloth->ShowContainer(controller->PlayerData->PlayerEquipment[1]);
	Widget_Shoes->ShowContainer(controller->PlayerData->PlayerEquipment[2]);
	Widget_Bag->ShowContainer(controller->PlayerData->PlayerEquipment[3]);
	Widget_Weapon->ShowContainer(controller->PlayerData->PlayerEquipment[4]);
}
