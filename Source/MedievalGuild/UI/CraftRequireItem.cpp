// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftRequireItem.h"
#include "Kismet/GameplayStatics.h"
#include "../Item/ItemDataManager.h"
#include "../Framework/TranslateManager.h"


void UCraftRequireItem::SetItemInfo(int index, int ownCount, int requireCount)
{
	if (!TSManager) TSManager = Cast<ATranslateManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATranslateManager::StaticClass()));

	UItemData* targetItem = UItemDataManager::GetInstance()->FindItemData(index);

	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(UItemDataManager::GetInstance()->Get2DSpriteForItem(targetItem));
	Image->SetBrush(NewBrush);
	Name->SetText(TSManager->TranslateTexts(FText::FromString(targetItem->name)));
	Count->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), ownCount, requireCount)));
}
