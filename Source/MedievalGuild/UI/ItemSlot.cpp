// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSlot->OnPressed.AddDynamic(this, &UItemSlot::OnPressedSlot);
	ItemSlot->OnReleased.AddDynamic(this, &UItemSlot::OnReleasedSlot);
}

void UItemSlot::OnPressedSlot()
{
	// 이동 활성화
}

void UItemSlot::OnReleasedSlot()
{

}
