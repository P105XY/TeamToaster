// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine.h"
#include "MainPlayer.h"
#include "PlayerHud.generated.h"

/**
 *
 */
UCLASS()
class KNN_API APlayerHud : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture2D* currentCrosshair;
	UPROPERTY(EditAnywhere)
		class AMainPlayer* mainPlayer;

	APlayerHud();

	void VisibleHUD();
	void HideHUD();

	virtual void DrawHUD() override;
};
