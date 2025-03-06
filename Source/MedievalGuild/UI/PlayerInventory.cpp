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
}

void UPlayerInventory::NativeConstruct()
{
	if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemSlotFinder"));
	if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemBaseFinder"));
	if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ItemMoveSlotFinder"));
	if (!ContainerWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Fail Load ContainerFinder"));

	PlayerInventoryInitSetting();
}

void UPlayerInventory::PlayerInventoryInitSetting()
{

	// ContainerSlot
	UContainerWidget* Widget_Container = CreateWidget<UContainerWidget>(GetWorld(), ContainerWidget);
	Widget_Container->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass);

	UHorizontalBoxSlot* Slot_Inventory = InventorySlot->AddChildToHorizontalBox(Widget_Container);
	Slot_Inventory->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Inventory->SetHorizontalAlignment(HAlign_Fill);
	Slot_Inventory->SetVerticalAlignment(VAlign_Fill);
	// 각 파트 위젯을 가져와서 배치
	// initsetting 하기



}
