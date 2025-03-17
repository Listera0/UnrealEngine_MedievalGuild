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
	InventorySlot->AddChildToHorizontalBox(Widget_Equipment);
	PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Collapsed);

	// MerchantWidget
	Widget_Merchant = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Merchant->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, EContainerCategory::Container, 6, 4);
	InventorySlot->AddChildToHorizontalBox(Widget_Merchant);
	PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Collapsed);

	// InventorySlot
	Widget_Inventory = CreateWidget<UPlayerContainerWidget>(GetWorld(), Blueprints->InventoryWidget);
	Widget_Inventory->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, EContainerCategory::Inventory, 6, 6);
	InventorySlot->AddChildToHorizontalBox(Widget_Inventory);
	PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Collapsed);

	// TradeSlot
	Widget_Trade = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Trade->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, EContainerCategory::Container, 6, 4);
	InventorySlot->AddChildToHorizontalBox(Widget_Trade);
	PanelVisibleSetting(Widget_Trade, ESlateVisibility::Collapsed);

	// ContainerSlot
	Widget_Container = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Container->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, EContainerCategory::Container, 6, 4);
	InventorySlot->AddChildToHorizontalBox(Widget_Container);
	PanelVisibleSetting(Widget_Container, ESlateVisibility::Collapsed);

	// StorageSlot
	Widget_Storage = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Storage->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, EContainerCategory::Container, 6, 4);
	InventorySlot->AddChildToHorizontalBox(Widget_Storage);
	PanelVisibleSetting(Widget_Storage, ESlateVisibility::Collapsed);
}

void UPlayerInventory::PanelVisibleSetting(int value)
{
	if (value == 0) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Trade, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Container, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Hidden);
	}
	else if (value == 1) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Trade, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Container, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Collapsed);
	}
	else if (value == 2) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Trade, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Container, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Visible);
	}
	else if (value == 3) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Trade, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Container, ESlateVisibility::Collapsed);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Visible);
	}
}

void UPlayerInventory::PanelVisibleSetting(UUserWidget* widget, ESlateVisibility visible)
{
	widget->SetVisibility(visible);
	UHorizontalBoxSlot* boxSlot = Cast<UHorizontalBoxSlot>(widget->Slot);
	boxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	boxSlot->SetHorizontalAlignment(HAlign_Fill);
	boxSlot->SetVerticalAlignment(VAlign_Fill);
}