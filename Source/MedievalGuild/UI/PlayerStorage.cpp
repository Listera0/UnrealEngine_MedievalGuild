// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStorage.h"
#include "../Framework/PlayerCharacterController.h"

void UPlayerStorage::ShowContainer(TArray<FInventoryData*>& data)
{
	Super::ShowContainer(data);

	OwnGold->SetText(FText::FromString(FString::Printf(TEXT("%d G"), GetTotalGold())));
}

int UPlayerStorage::GetTotalGold()
{
	int GoldCount = 0;
	APlayerCharacterController* Controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	for (FInventoryData* data : Controller->PlayerData->GetTargetContainer(ContainerCategory)) {
		if (data->ItemData->index == 0) {
			GoldCount += data->ItemCount;
		}
	}
	return GoldCount;
}
