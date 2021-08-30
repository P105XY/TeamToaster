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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "crosshair")
		TSubclassOf<class UUserWidget> wCrosshair;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "crosshair")
		UUserWidget* crosshair;

	bool bCrosshairvisible;

	void SetVisibleHUD();
	void SetRemoveHUD();
};
