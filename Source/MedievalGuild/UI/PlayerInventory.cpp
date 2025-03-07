// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

UPlayerInventory::UPlayerInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	if (ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemMoveSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemMoveSlot"));
	if (ItemMoveSlotFinder.Succeeded()) ItemMoveSlotClass = ItemMoveSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ContainerFinder(TEXT("/Game/Blueprint/UI/WB_ContainerWidget"));
	if (ContainerFinder.Succeeded()) ContainerWidget = ContainerFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryFinder(TEXT("/Game/Blueprint/UI/WB_PlayerContainerWidget"));
	if (InventoryFinder.Succeeded()) InventoryWidget = InventoryFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> EquipmentFinder(TEXT("/Game/Blueprint/UI/WB_EquipmentWidget"));
	if (EquipmentFinder.Succeeded()) EquipmentWidget = EquipmentFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> GearFinder(TEXT("/Game/Blueprint/UI/WB_GearWidget"));
	if (GearFinder.Succeeded()) GearWidget = GearFinder.Class;
}

void UPlayerInventory::NativeConstruct()
{
	if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemSlotFinder"));
	if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemBaseFinder"));
	if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemMoveSlotFinder"));
	if (!ContainerWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ContainerFinder"));
	if (!InventoryWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load InventoryFinder"));
	if (!EquipmentWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load EquipmentFinder"));
	if (!GearWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load GearFinder"));

	PlayerInventoryInitSetting();
}

void UPlayerInventory::PlayerInventoryInitSetting()
{
	// EquipmentWidget
	UEquipmentWidget* Widget_Equipment = CreateWidget<UEquipmentWidget>(GetWorld(), EquipmentWidget);
	Widget_Equipment->InitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, GearWidget);

	UHorizontalBoxSlot* Slot_Equipment = InventorySlot->AddChildToHorizontalBox(Widget_Equipment);
	Slot_Equipment->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Equipment->SetHorizontalAlignment(HAlign_Fill);
	Slot_Equipment->SetVerticalAlignment(VAlign_Fill);

	// InventorySlot
	UPlayerContainerWidget* Widget_Inventory = CreateWidget<UPlayerContainerWidget>(GetWorld(), InventoryWidget);
	Widget_Inventory->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, 6, 6);

	UHorizontalBoxSlot* Slot_Inventory = InventorySlot->AddChildToHorizontalBox(Widget_Inventory);
	Slot_Inventory->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Inventory->SetHorizontalAlignment(HAlign_Fill);
	Slot_Inventory->SetVerticalAlignment(VAlign_Fill);

	// ContainerSlot
	UContainerWidget* Widget_Container = CreateWidget<UContainerWidget>(GetWorld(), ContainerWidget);
	Widget_Container->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, 6, 4);
	Widget_Container->MakeItemToSlot(2, 2, 0);
	Widget_Container->MakeItemToSlot(3, 1, 1);
	Widget_Container->MakeItemToSlot(1, 2, 2);
	Widget_Container->MakeItemToSlot(2, 1, 3);

	UHorizontalBoxSlot* Slot_Container = InventorySlot->AddChildToHorizontalBox(Widget_Container);
	Slot_Container->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Container->SetHorizontalAlignment(HAlign_Fill);
	Slot_Container->SetVerticalAlignment(VAlign_Fill);
}
