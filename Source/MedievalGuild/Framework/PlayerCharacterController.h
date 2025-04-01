// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"

#include "../UI/Container_Base.h"
#include "../UI/PlayerInventory.h"
#include "../UI/ScreenUI.h"
#include "../UI/ItemInfoPanel.h"
#include "../UI/ItemInteractPanel.h"
#include "../Character/PlayerData.h"
#include "../Item/ItemDataManager.h"
#include "../Object/InteractObject_Base.h"

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

	void InitPlayerCameraLock();
	void InitSceenResolution();
	void InitMoveInput();
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
	void InitViewportScale();
	void CheckScreenUI();
	void CheckInteractDistance();
	void CheckInteractUIDistance();
	void OpenUISetting();
	void AllUIHidden();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerInventory> InventoryViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UScreenUI> ScreenViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItemInfoPanel> ItemInfoViewport = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UItemInteractPanel> ItemInteractPanel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> testwidget = nullptr;

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

	FVector2D LastMousePosition;

	bool bIsViewScaleInit;
	bool bIsUIOpened;
	bool bIsShiftPressed;
	bool bIsInteract;
	bool bIsInteractAction;
	bool bIsInteractItem;

public:
	UContainer_Base* GetTargetContainer(EContainerCategory category);
	void RecordMousePosition();
	inline bool IsShiftPressed() { return bIsShiftPressed; }
	inline bool IsInteractAction() { return bIsInteractAction; }
	bool bIsMovingItem;

	FHitResult hitResult;
	UPlayerInventory* InventoryUI = nullptr;
	UScreenUI* ScreenUI = nullptr;
	UItemInfoPanel* ItemInfoUI = nullptr;
	UItemInteractPanel* ItemInteractUI = nullptr;
	APlayerData* PlayerData = nullptr;
	AInteractObject_Base* InteractObj = nullptr;

	FVector2D ViewPortSize;

	class APlayerCharacter* PlayerCharacter = nullptr;
};
