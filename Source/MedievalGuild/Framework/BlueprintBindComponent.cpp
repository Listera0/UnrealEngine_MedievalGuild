// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintBindComponent.h"

// Sets default values for this component's properties
UBlueprintBindComponent::UBlueprintBindComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlot"));
	if (ItemSlotFinder.Succeeded()) ItemSlotClass = ItemSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemSlotImgFinder(TEXT("/Game/Blueprint/UI/WB_ItemSlotImg"));
	if (ItemSlotImgFinder.Succeeded()) ItemSlotImgClass = ItemSlotImgFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemBaseFinder(TEXT("/Game/Blueprint/UI/WB_ItemUI_Base"));
	if (ItemBaseFinder.Succeeded()) ItemBaseClass = ItemBaseFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ItemMoveSlotFinder(TEXT("/Game/Blueprint/UI/WB_ItemMoveSlot"));
	if (ItemMoveSlotFinder.Succeeded()) ItemMoveSlotClass = ItemMoveSlotFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ContainerFinder(TEXT("/Game/Blueprint/UI/WB_ContainerWidget"));
	if (ContainerFinder.Succeeded()) ContainerWidget = ContainerFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> StorageFinder(TEXT("/Game/Blueprint/UI/WB_PlayerStorage"));
	if (StorageFinder.Succeeded()) StorageWidget = StorageFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryFinder(TEXT("/Game/Blueprint/UI/WB_PlayerContainerWidget"));
	if (InventoryFinder.Succeeded()) InventoryWidget = InventoryFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> EquipmentFinder(TEXT("/Game/Blueprint/UI/WB_EquipmentWidget"));
	if (EquipmentFinder.Succeeded()) EquipmentWidget = EquipmentFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> TradeFinder(TEXT("/Game/Blueprint/UI/WB_TradeWidget"));
	if (TradeFinder.Succeeded()) TradeWidget = TradeFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> GearFinder(TEXT("/Game/Blueprint/UI/WB_GearWidget"));
	if (GearFinder.Succeeded()) GearWidget = GearFinder.Class;
}


// Called when the game starts
void UBlueprintBindComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ItemSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemSlotFinder"));
	if (!ItemSlotImgClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemSlotImgClass"));
	if (!ItemBaseClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemBaseFinder"));
	if (!ItemMoveSlotClass) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ItemMoveSlotFinder"));
	if (!ContainerWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load ContainerFinder"));
	if (!InventoryWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load InventoryFinder"));
	if (!EquipmentWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load EquipmentFinder"));
	if (!GearWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load GearFinder"));
	if (!TradeWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load TradeWidget"));
	if (!StorageWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load StorageWidget"));
	//if (!SellWidget) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Fail Load SellFinder"));
}


// Called every frame
void UBlueprintBindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

