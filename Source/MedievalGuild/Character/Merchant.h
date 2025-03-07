#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "../Item/ItemData.h"

#include "Merchant.generated.h"

UCLASS()
class MEDIEVALGUILD_API AMerchant : public AActor
{
	GENERATED_BODY()

public:
	AMerchant();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UItemData* SellItem(int index, int Count);

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merchant")
	UCapsuleComponent* Collision = nullptr;

private:
	TArray<UItemData*> ItemDatas;
};
