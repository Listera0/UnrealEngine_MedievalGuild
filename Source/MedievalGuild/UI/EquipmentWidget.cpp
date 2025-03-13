// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

void UEquipmentWidget::InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass, 
									TSubclassOf<UUserWidget> gearWidget)
{
	ItemSlotClass = itemSlotClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	GearWidget = gearWidget;

	// Helmet
	UGearWidget* Widget_Helmet = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Helmet->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Equipment, 2, 2);
	UCanvasPanelSlot* Slot_Helmet = HelmetSlot->AddChildToCanvas(Widget_Helmet);
	Slot_Helmet->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Cloth
	UGearWidget* Widget_Cloth = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Cloth->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Equipment, 2, 2);
	UCanvasPanelSlot* Slot_Cloth = ClothSlot->AddChildToCanvas(Widget_Cloth);
	Slot_Cloth->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Shoes
	UGearWidget* Widget_Shoes = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Shoes->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Equipment, 2, 2);
	UCanvasPanelSlot* Slot_Shoes = ShoesSlot->AddChildToCanvas(Widget_Shoes);
	Slot_Shoes->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Bag
	UGearWidget* Widget_Bag = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Bag->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Equipment, 3, 3);
	UCanvasPanelSlot* Slot_Bag = BagSlot->AddChildToCanvas(Widget_Bag);
	Slot_Bag->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	// Weapon
	UGearWidget* Widget_Weapon = CreateWidget<UGearWidget>(GetWorld(), gearWidget);
	Widget_Weapon->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Equipment, 3, 1);
	UCanvasPanelSlot* Slot_Weapon = WeaponSlot->AddChildToCanvas(Widget_Weapon);
	Slot_Weapon->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
}
