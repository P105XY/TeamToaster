// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine.h"
#include "CrossHair.generated.h"

/**
 *
 */
UCLASS()
class KNN_API ACrossHair : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UTexture2D* Crosshair;

public:
	virtual void DrawHUD() override;
};
