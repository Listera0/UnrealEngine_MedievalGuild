// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"
#include "../Framework/PlayerCharacterController.h"

UPlayerInventory::UPlayerInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPlayerInventory::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	GameManager = Cast<AGameManager>(UGameplayStatics::GetGameMode(GetWorld()));
	Blueprints = GameManager->Blueprints;

	PlayerInventoryInitSetting();
}

void UPlayerInventory::PlayerInventoryInitSetting()
{
	TArray<TSubclassOf<UUserWidget>> InitWidgetClass;
	InitWidgetClass = { Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass, Blueprints->QuestSlotWidget };
	
	// >> LeftSide ------------------------------------------------------------------------------------
	// EquipmentWidget
	Widget_Equipment = CreateWidget<UEquipmentWidget>(GetWorld(), Blueprints->EquipmentWidget);
	Widget_Equipment->InitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->GearWidget, Blueprints->ItemSlotImgClass);
	InventorySlot->AddChildToHorizontalBox(Widget_Equipment);

	// MerchantWidget
	Widget_Merchant = CreateWidget<UMerchantInventory>(GetWorld(), Blueprints->MerchantInventoryWidget);
	Widget_Merchant->MerchantPanelInitSetting(InitWidgetClass, EContainerCategory::Merchant, FVector2D(6, 8));
	InventorySlot->AddChildToHorizontalBox(Widget_Merchant);

	// CraftListWidget
	Widget_CraftInventory = CreateWidget<UCraftInventory>(GetWorld(), Blueprints->CraftInventoryWidget);
	Widget_CraftInventory->CraftInventoryInitSetting(InitWidgetClass, EContainerCategory::CraftInventory, FVector2D(6, 8));
	InventorySlot->AddChildToHorizontalBox(Widget_CraftInventory);

	// >> MiddleSide ------------------------------------------------------------------------------------
	// InventorySlot
	Widget_Inventory = CreateWidget<UPlayerContainerWidget>(GetWorld(), Blueprints->InventoryWidget);
	Widget_Inventory->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass,
											EContainerCategory::Inventory, FVector2D(6, 6));
	InventorySlot->AddChildToHorizontalBox(Widget_Inventory);

	// TradeSlot
	Widget_Trade = CreateWidget<UTradeWidget>(GetWorld(), Blueprints->TradeWidget);
	Widget_Trade->InitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass, Blueprints->GearWidget);
	InventorySlot->AddChildToHorizontalBox(Widget_Trade);

	// QuestPlayerSlot
	Widget_QuestInfoPanel = CreateWidget<UQuestInfoPanel>(GetWorld(), Blueprints->QuestInfoWidget);
	Widget_QuestInfoPanel->QuestInfoInitSetting();
	InventorySlot->AddChildToHorizontalBox(Widget_QuestInfoPanel);

	// CraftRequire
	Widget_CraftRequire = CreateWidget<UCraftRequire>(GetWorld(), Blueprints->CraftRequireWidget);
	Widget_CraftRequire->CraftRequireInitSetting(Blueprints->CraftRequireItemWidget);
	InventorySlot->AddChildToHorizontalBox(Widget_CraftRequire);

	// >> RightSide ------------------------------------------------------------------------------------
	// ContainerSlot
	Widget_Container = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Container->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass, 
											EContainerCategory::Container, FVector2D(6, 4));
	InventorySlot->AddChildToHorizontalBox(Widget_Container);

	Widget_EnemyContainer = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_EnemyContainer->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass,
		EContainerCategory::EnemyInventory, FVector2D(6, 4));
	InventorySlot->AddChildToHorizontalBox(Widget_EnemyContainer);

	// StorageSlot
	Widget_Storage = CreateWidget<UPlayerStorage>(GetWorld(), Blueprints->StorageWidget);
	Widget_Storage->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, Blueprints->ItemSlotImgClass, 
											EContainerCategory::Storage, FVector2D(6, 8));
	InventorySlot->AddChildToHorizontalBox(Widget_Storage);

	// QuestPlayerSlot
	InitWidgetClass.Empty();
	InitWidgetClass = { Blueprints->QuestSlotWidget };
	Widget_QuestPlayerPanel = CreateWidget<UQuestPlayerPanel>(GetWorld(), Blueprints->QuestPlayerWidget);
	Widget_QuestPlayerPanel->QuestPlayerPanelInitSetting(InitWidgetClass);
	InventorySlot->AddChildToHorizontalBox(Widget_QuestPlayerPanel);

	// OptionMenu
	Widget_OptionMenu = CreateWidget<UOptionMenu>(GetWorld(), Blueprints->OptionMenuWidget);
	Widget_OptionMenu->OptionMenuInitSetting();
	InventorySlot->AddChildToHorizontalBox(Widget_OptionMenu);

	// >> Other ----------------------------------------------------------------------------------------
	// StageMap
	Widget_StageMap = CreateWidget<UStageMap>(GetWorld(), Blueprints->StageMapWidget);
	Widget_StageMap->StageMapInitSetting();
	InventorySlot->AddChildToHorizontalBox(Widget_StageMap);

	AllPanelCollapsed();
}

void UPlayerInventory::PanelVisibleSetting(int value)
{
	AllPanelCollapsed();

	if (value == 0) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_OptionMenu, ESlateVisibility::Visible);
	}
	else if (value == 1) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Container, ESlateVisibility::Visible);
	}
	else if (value == 2) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Visible);
	}
	else if (value == 3) {
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Trade, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Visible);
	}
	else if (value == 4) {
		PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_QuestInfoPanel, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_QuestPlayerPanel, ESlateVisibility::Visible);
	}
	else if (value == 5) {
		PanelVisibleSetting(Widget_QuestPlayerPanel, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_QuestInfoPanel, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_OptionMenu, ESlateVisibility::Visible);
	}
	else if (value == 6) {
		PanelVisibleSetting(Widget_CraftInventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_CraftRequire, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Storage, ESlateVisibility::Visible);
	}
	else if (value == 7) {
		PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Visible);
		PanelVisibleSetting(Widget_EnemyContainer, ESlateVisibility::Visible);
	}
	else if (value == 11) {
		PanelVisibleSetting(Widget_StageMap, ESlateVisibility::Visible);
	}
}

void UPlayerInventory::AllPanelCollapsed()
{
	PanelVisibleSetting(Widget_Equipment, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_Merchant, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_Inventory, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_Trade, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_QuestInfoPanel, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_Container, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_Storage, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_QuestPlayerPanel, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_OptionMenu, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_StageMap, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_CraftInventory, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_CraftRequire, ESlateVisibility::Collapsed);
	PanelVisibleSetting(Widget_EnemyContainer, ESlateVisibility::Collapsed);
}

void UPlayerInventory::PanelVisibleSetting(UUserWidget* widget, ESlateVisibility visible)
{
	widget->SetVisibility(visible);

	if (visible == ESlateVisibility::Visible) {
		InventorySlot->RemoveChild(widget);
		InventorySlot->AddChildToHorizontalBox(widget);
		UHorizontalBoxSlot* boxSlot = Cast<UHorizontalBoxSlot>(widget->Slot);
		boxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		boxSlot->SetHorizontalAlignment(HAlign_Fill);
		boxSlot->SetVerticalAlignment(VAlign_Fill);

		PanelOpenSetting(widget);
	}
}

void UPlayerInventory::PanelOpenSetting(UUserWidget* widget)
{
	if (widget == Widget_Inventory) {
		Widget_Inventory->ShowContainer(PlayerController->PlayerData->GetTargetContainer(Widget_Inventory->ContainerCategory));
	}
	else if (widget == Widget_Equipment) {
		Widget_Equipment->ShowContainer();
	}
	else if (widget == Widget_Storage) {
		Widget_Storage->ShowContainer(PlayerController->PlayerData->GetTargetContainer(Widget_Storage->ContainerCategory));
	}
	else if (widget == Widget_Trade) {
		Widget_Trade->ShowContainer();
	}
	else if (widget == Widget_Container || widget == Widget_Merchant || widget == Widget_CraftInventory) {
		PlayerController->InteractObj->SetContainerUI();
	}
	else if (widget == Widget_EnemyContainer) {
		PlayerController->InteractCharacter->SetContainerUI();
	}
	else if (widget == Widget_QuestInfoPanel) {
		Widget_QuestInfoPanel->ShowQuestDetail(nullptr);
	}
	else if (widget == Widget_QuestPlayerPanel) {
		Widget_QuestPlayerPanel->ShowQuestList();
	}
}
