// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "../UI/Container_Base.h"
#include "../UI/PlayerInventory.h"
#include "../UI/Trade.h"
#include "../UI/ScreenUI.h"
#include "../Character/PlayerData.h"

#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALGUILD_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCharacterController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void InitViewport();
	void InitPlayerData();

	void InputMove(const FInputActionValue& Value);
	void InputCameraMove(const FInputActionValue& Value);
	void InputPressRunKey(const FInputActionValue& Value);
	void InputRealeaseRunKey(const FInputActionValue& Value);
	void InputStealthToggle(const FInputActionValue& Value);
	void InputAttackAction(const FInputActionValue& Value);
	void InputInventoryToggle(const FInputActionValue& Value);
	void InputInteractAction(const FInputActionValue& Value);

	FHitResult lineTraceCheckTag(FName tag);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerInventory> InventoryViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTrade> TradeViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UScreenUI> ScreenViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* MoveCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* MoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* RunAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* StealthAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* AttackAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* InventoryToggle = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputComponent")
	class UInputAction* InteractAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputOption")
	float CameraSensitive = 0.5f;

private:
	class APlayerCharacter* PlayerCharacter = nullptr;

	UPlayerInventory* InventoryUI = nullptr;
	UTrade* TradeUI = nullptr;
	UScreenUI* ScreenUI = nullptr;
	APlayerData* PlayerData = nullptr;

	bool bIsInteract;
	FHitResult hitResult;
};
