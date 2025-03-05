// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "../UI/PlayerInventory.h"
#include "../UI/Container_Base.h"

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
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void InitViewport();

	void InputMove(const FInputActionValue& Value);
	void InputCameraMove(const FInputActionValue& Value);
	void InputPressRunKey(const FInputActionValue& Value);
	void InputRealeaseRunKey(const FInputActionValue& Value);
	void InputStealthToggle(const FInputActionValue& Value);
	void InputAttackAction(const FInputActionValue& Value);
	void InputInventoryToggle(const FInputActionValue& Value);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UContainer_Base> InventoryViewport = nullptr;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputOption")
	float CameraSensitive = 0.5f;

private:
	class APlayerCharacter* PlayerCharacter = nullptr;

	UContainer_Base* InventoryUI = nullptr;
};
