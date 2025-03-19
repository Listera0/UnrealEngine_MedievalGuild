// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"

void UTradeWidget::InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass,
								TSubclassOf<UUserWidget> gearWidget)
{
	ItemSlotClass = itemSlotClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	GearWidget = gearWidget;

	Widget_Trade = CreateWidget<UGearWidget>(GetWorld(), GearWidget);
	Widget_Trade->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, EContainerCategory::Trade, FVector2D(6, 4));
	UCanvasPanelSlot* Slot_Trade = TradeSlot->AddChildToCanvas(Widget_Trade);
	Slot_Trade->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));

	PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	SellBuyButton->OnClicked.AddDynamic(this, &UTradeWidget::BindSellBuyButton);
}

void UTradeWidget::ShowContainer()
{
	TArray<FInventoryData*> items = PlayerController->PlayerData->GetTargetContainer(Widget_Trade->ContainerCategory);
	Widget_Trade->ShowContainer(items);
	ShowTotalPrice();
}

void UTradeWidget::ShowTotalPrice()
{
	TotalPrice = 0;
	TArray<FInventoryData*> items = PlayerController->PlayerData->GetTargetContainer(Widget_Trade->ContainerCategory);

	if (items.Num() == 0) {
		PriceText->SetText(FText::FromString(FString(TEXT("0 G"))));
		Cast<UTextBlock>(SellBuyButton->GetChildAt(0))->SetText(FText::FromString(FString("")));
		bIsBuy = false; bIsSell = false; bIsEnoughCurrency = false; ButtonSetting(NormalColor);
		return;
	}

	for (FInventoryData* data : items) { TotalPrice += data->ItemData->price * data->ItemCount; }
	PriceText->SetText(FText::FromString(FString::Printf(TEXT("%d G"), TotalPrice)));

	if (bIsBuy) { 
		Cast<UTextBlock>(SellBuyButton->GetChildAt(0))->SetText(FText::FromString(FString("Buy"))); 
		if (PlayerController->PlayerData->GetPlayerCurrency() < TotalPrice) { bIsEnoughCurrency = false; ButtonSetting(FailColor); }
		else { bIsEnoughCurrency = true; ButtonSetting(SuccessColor); }
	}
	else if (bIsSell) { 
		Cast<UTextBlock>(SellBuyButton->GetChildAt(0))->SetText(FText::FromString(FString("Sell"))); 
		bIsEnoughCurrency = true; ButtonSetting(SuccessColor);
	}
	else {
		Cast<UTextBlock>(SellBuyButton->GetChildAt(0))->SetText(FText::FromString(FString("")));
		bIsEnoughCurrency = false; ButtonSetting(NormalColor);
	}
}

bool UTradeWidget::CanMoveItem(EContainerCategory from)
{
	if (bIsSell && from == EContainerCategory::Merchant) return false;
	if (bIsBuy && from == EContainerCategory::Storage) return false;

	return true;
}

// for merchant item click
void UTradeWidget::SelectBuyItem(FInventoryData* item)
{
	PlayerController->PlayerData->GetTargetContainer(Widget_Trade->ContainerCategory).Empty();

	if (item) {
		FInventoryData* tempItem = new FInventoryData(item->SlotIndex, item->ItemData, 1);
		PlayerController->PlayerData->GetTargetContainer(Widget_Trade->ContainerCategory).Add(tempItem);
		bIsBuy = true;
	}
	else {
		bIsBuy = false;
	}

	ShowTotalPrice();
}

void UTradeWidget::ButtonSetting(FColor color)
{
	FButtonStyle buttonStyle;
	FSlateBrush RoundBrush;

	RoundBrush.TintColor = FSlateColor(color);
	RoundBrush.DrawAs = ESlateBrushDrawType::RoundedBox;

	buttonStyle.SetNormal(RoundBrush);
	buttonStyle.SetHovered(RoundBrush);
	buttonStyle.SetPressed(RoundBrush);

	buttonStyle.NormalPadding = 0.0f;
	buttonStyle.PressedPadding = 0.0f;

	SellBuyButton->SetStyle(buttonStyle);
}

void UTradeWidget::BindSellBuyButton()
{
	if (bIsSell) {
		FInventoryData* Coin = new FInventoryData(FVector2D(-1.0f), UItemDataManager::GetInstance()->FindItemData(0), TotalPrice);
		PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), 
															Coin, PlayerController->GetTargetContainer(EContainerCategory::Storage));
		PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade).Empty();
		ShowTotalPrice();
		PlayerController->GetTargetContainer(EContainerCategory::Storage)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage));
		Widget_Trade->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade));
	}
	else if (bIsBuy) {
		if (bIsEnoughCurrency) {
			FInventoryData* Item = new FInventoryData(FVector2D(-1.0f), PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade)[0]->ItemData, 1);
			PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), 
																Item, PlayerController->GetTargetContainer(EContainerCategory::Storage));
			PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), 
															UItemDataManager::GetInstance()->FindItemData(0), 1, true);

			ShowTotalPrice();
			PlayerController->GetTargetContainer(EContainerCategory::Storage)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage));
			Widget_Trade->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade));
		}
	}
}
