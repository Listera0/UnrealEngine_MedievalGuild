// Fill out your copyright notice in the Description page of Project Settings.


#include "Trade.h"

UTrade::UTrade(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UTrade::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = Cast<AGameManager>(UGameplayStatics::GetGameMode(GetWorld()));
	Blueprints = GameManager->Blueprints;

	TradePanelInitSetting();
}

void UTrade::TradePanelInitSetting()
{
	// Merchant
	UContainerWidget* Widget_Merchant = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Merchant->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, 6, 10);

	UHorizontalBoxSlot* Slot_Merchant = TradeSlot->AddChildToHorizontalBox(Widget_Merchant);
	Slot_Merchant->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Merchant->SetHorizontalAlignment(HAlign_Fill);
	Slot_Merchant->SetVerticalAlignment(VAlign_Fill);

	// Buy
	UBuyWidget* Widget_Buy = CreateWidget<UBuyWidget>(GetWorld(), Blueprints->BuyWidget);
	//Widget_Merchant->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, 6, 10);

	UHorizontalBoxSlot* Slot_Buy = TradeSlot->AddChildToHorizontalBox(Widget_Buy);
	Slot_Buy->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Buy->SetHorizontalAlignment(HAlign_Fill);
	Slot_Buy->SetVerticalAlignment(VAlign_Fill);

	// Storage
	UContainerWidget* Widget_Storage = CreateWidget<UContainerWidget>(GetWorld(), Blueprints->ContainerWidget);
	Widget_Storage->ContainerInitSetting(Blueprints->ItemSlotClass, Blueprints->ItemBaseClass, Blueprints->ItemMoveSlotClass, 6, 10);

	UHorizontalBoxSlot* Slot_Storage = TradeSlot->AddChildToHorizontalBox(Widget_Storage);
	Slot_Storage->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
	Slot_Storage->SetHorizontalAlignment(HAlign_Fill);
	Slot_Storage->SetVerticalAlignment(VAlign_Fill);
}
