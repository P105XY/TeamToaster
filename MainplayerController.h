// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CrossHair.h"
#include "MainPlayer.h"
#include "PlayerHud.h"
#include "MainplayerController.generated.h"

/**
 *
 */
UCLASS()
class KNN_API AMainplayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	AMainplayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf<class UUserWidget> wCrosshair;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		UUserWidget* crosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf<class UUserWidget> wInventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		UUserWidget* inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf<class UUserWidget> wQuickSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		UUserWidget* quickslot;

	bool bCrosshairvisible;

	void SetVisibleHUD();
	void SetRemoveHUD();

	void SetVisiblePause();
	void SetRemovePause();

	void SetVisibleQuickSlot();
	void SetRemoveQuickSlot();
};
