// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPlayerInventory::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = Cast<AGameManager>(UGameplayStatics::GetGameMode(GetWorld()));
	Blueprints = GameManager->Blueprints;

	PlayerInventoryInitSetting();
}

void UPlayerInventory::PlayerInventoryInitSetting()
{
	// EquipmentWidget
	Widget_Equipment = CreateWidget<UEquipmentWidget>(GetWorld(), Blueprints->EquipmentWidget);
	Widget_Equipment->InitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->GearWidget);

	UHorizontalBoxSlot* Slot_Equipment = InventorySlot->AddChildToHorizontalBox(Widget_Equipment);
	Slot_Equipment->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Equipment->SetHorizontalAlignment(HAlign_Fill);
	Slot_Equipment->SetVerticalAlignment(VAlign_Fill);

	// InventorySlot
	Widget_Inventory = CreateWidget<UPlayerContainerWidget>(GetWorld(), Blueprints->InventoryWidget);
	Widget_Inventory->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, 6, 6);

	UHorizontalBoxSlot* Slot_Inventory = InventorySlot->AddChildToHorizontalBox(Widget_Inventory);
	Slot_Inventory->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Inventory->SetHorizontalAlignment(HAlign_Fill);
	Slot_Inventory->SetVerticalAlignment(VAlign_Fill);

	// ContainerSlot
	Widget_Container = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Container->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, 6, 4);
	Widget_Container->MakeItemToSlot(2, 2, 0);
	Widget_Container->MakeItemToSlot(3, 1, 1);
	Widget_Container->MakeItemToSlot(1, 2, 2);
	Widget_Container->MakeItemToSlot(2, 1, 3);

	UHorizontalBoxSlot* Slot_Container = InventorySlot->AddChildToHorizontalBox(Widget_Container);
	Slot_Container->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Container->SetHorizontalAlignment(HAlign_Fill);
	Slot_Container->SetVerticalAlignment(VAlign_Fill);
}
