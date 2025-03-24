// Fill out your copyright notice in the Description page of Project Settings.


#include "TradeWidget.h"
#include "../Framework/PlayerCharacterController.h"
#include "../Item/ItemDataManager.h"

void UTradeWidget::InitSetting(TSubclassOf<UUserWidget> itemSlotClass, TSubclassOf<UUserWidget> itemBaseClass, TSubclassOf<UUserWidget> itemMoveSlotClass,
								TSubclassOf<UUserWidget> itemSlotImgClass, TSubclassOf<UUserWidget> gearWidget)
{
	ItemSlotClass = itemSlotClass;
	ItemSlotImgClass = itemSlotImgClass;
	ItemBaseClass = itemBaseClass;
	ItemMoveSlotClass = itemMoveSlotClass;
	GearWidget = gearWidget;

	NormalColor = FLinearColor(0.5f, 0.5f, 0.5f);
	FailColor = FLinearColor(0.5f, 0.2f, 0.2f);
	SuccessColor = FLinearColor(0.2f, 0.25f, 0.2f);

	Widget_Trade = CreateWidget<UGearWidget>(GetWorld(), GearWidget);
	Widget_Trade->ContainerInitSetting(ItemSlotClass, ItemBaseClass, ItemMoveSlotClass, ItemSlotImgClass, EContainerCategory::Trade, FVector2D(6, 4));
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

void UTradeWidget::ResetContainer()
{
	if (bIsBuy) { SelectBuyItem(nullptr); }
	if (bIsSell) {
		TArray<FInventoryData*> targetData = PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade);
		for (FInventoryData* data : targetData) {
			UItemSlot* targetSlot = Widget_Trade->GetContainerSlot(data->SlotIndex);
			targetSlot->SlotButtonShiftClick();
		}

		bIsSell = false;
	}
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
		if (PlayerController->PlayerData->GetPlayerCurrency() < TotalPrice || 
			PlayerController->PlayerData->FindEmptySlot(PlayerController->PlayerData->GetTargetContainer
				(EContainerCategory::Storage), PlayerController->GetTargetContainer(EContainerCategory::Storage), items[0]) == FVector2D(-1.0f))
		{ 
			bIsEnoughCurrency = false; 
			ButtonSetting(FailColor); 
		}
		else { 
			bIsEnoughCurrency = true; 
			ButtonSetting(SuccessColor); 
		}
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

	ShowContainer();
}

void UTradeWidget::ButtonSetting(FLinearColor color)
{
	FButtonStyle buttonStyle;
	FSlateBrush RoundBrush;
	FSlateBrushOutlineSettings OutlineSetting;

	OutlineSetting.Color = color;
	OutlineSetting.RoundingType = ESlateBrushRoundingType::FixedRadius;
	OutlineSetting.CornerRadii = FVector4(4.0f, 4.0f, 4.0f, 4.0f);

	RoundBrush.TintColor = FSlateColor(color);
	RoundBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
	RoundBrush.OutlineSettings = OutlineSetting;

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
		Widget_Trade->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade));
		PlayerController->GetTargetContainer(EContainerCategory::Storage)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage));
	}
	else if (bIsBuy) {
		if (bIsEnoughCurrency) {
			FInventoryData* Item = new FInventoryData(FVector2D(-1.0f), PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Trade)[0]->ItemData, 1);
			PlayerController->PlayerData->AddItemToAllWork(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), 
																Item, PlayerController->GetTargetContainer(EContainerCategory::Storage));
			PlayerController->PlayerData->RemoveItemTo(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage), 
															UItemDataManager::GetInstance()->FindItemData(0), TotalPrice, true);

			ShowTotalPrice();
			PlayerController->GetTargetContainer(EContainerCategory::Storage)->ShowContainer(PlayerController->PlayerData->GetTargetContainer(EContainerCategory::Storage));
		}
	}
}
