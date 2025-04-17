// Fill out your copyright notice in the Description page of Project Settings.


#include "MerchantInventory.h"
#include "Components/VerticalBoxSlot.h"
#include "../Framework/PlayerCharacterController.h"
#include "QuestSlot.h"

void UMerchantInventory::ShowContainer(TArray<FInventoryData*>& data)
{
	Super::ShowContainer(data);

	if (!PlayerController) { PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController()); }

	MerchantName->SetText(FText::FromName(PlayerController->InteractObj->ObjectName));
}

void UMerchantInventory::MerchantPanelInitSetting(TArray<TSubclassOf<UUserWidget>> InitWidgetClass, EContainerCategory category, FVector2D size)
{
	ContainerInitSetting(InitWidgetClass[0], InitWidgetClass[1], InitWidgetClass[2], InitWidgetClass[3], category, size);
	QuestSlotClass = InitWidgetClass[4];

	TradeAndQuest->OnClicked.AddDynamic(this, &UMerchantInventory::SwitchPanelScreen);
}

void UMerchantInventory::MakeQuestListPanel()
{
	QuestSlotGrid->ClearChildren();

	int TotalQuestCount = 0;
	for(UUserWidget* quest : QuestList) {
		UQuestSlot* newQuestSlot = CreateWidget<UQuestSlot>(GetWorld(), QuestSlotClass);
		FButtonStyle buttonStyle;
		FSlateBrush borderBrush;
		borderBrush.TintColor = FLinearColor(0.5f, 0.2f, 0.2f, 1.0f);
		borderBrush.DrawAs = ESlateBrushDrawType::Box;
		buttonStyle.SetNormal(borderBrush);
		buttonStyle.SetHovered(borderBrush);
		buttonStyle.SetPressed(borderBrush);
		buttonStyle.NormalPadding = 0.0f;
		buttonStyle.PressedPadding = 0.0f;
		newQuestSlot->QuestSlot->SetStyle(buttonStyle);

		UVerticalBoxSlot* GridSlot = QuestSlotGrid->AddChildToVerticalBox(newQuestSlot);
		GridSlot->SetPadding(FMargin(0.0f, 0.0f, 0.0f, 1.0f));
		GridSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		GridSlot->SetHorizontalAlignment(HAlign_Fill);
		GridSlot->SetVerticalAlignment(VAlign_Fill);

		TotalQuestCount++;
	}

	Cast<UCanvasPanelSlot>(QuestSlot->Slot)->SetSize(FVector2D(500.0f, (float)(TotalQuestCount) * 50.0f));
}

void UMerchantInventory::SwitchPanelScreen()
{
	if (!PlayerController) { PlayerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController()); }

	if (bIsSwitched) {
		bIsSwitched = false;
		ContainerSlot->SetVisibility(ESlateVisibility::Visible);
		QuestSlot->SetVisibility(ESlateVisibility::Collapsed);
		Cast<UTextBlock>(TradeAndQuest->GetChildAt(0))->SetText(FText::FromString("Show Quest"));
		PlayerController->InventoryUI->PanelVisibleSetting(3);
	}
	else {
		bIsSwitched = true;
		MakeQuestListPanel();
		ContainerSlot->SetVisibility(ESlateVisibility::Collapsed);
		QuestSlot->SetVisibility(ESlateVisibility::Visible);
		Cast<UTextBlock>(TradeAndQuest->GetChildAt(0))->SetText(FText::FromString("Show Trade"));
		PlayerController->InventoryUI->PanelVisibleSetting(4);
	}	
}
