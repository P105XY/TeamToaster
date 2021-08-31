// Fill out your copyright notice in the Description page of Project Settings.


#include "MainplayerController.h"

AMainplayerController::AMainplayerController()
{

}

void AMainplayerController::BeginPlay()
{
	Super::BeginPlay();

	if (wCrosshair)
	{
		this->crosshair = CreateWidget<UUserWidget>(this, wCrosshair);
		if (crosshair)
		{
			crosshair->AddToViewport();
			crosshair->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (wInventory)
	{
		this->inventory = CreateWidget<UUserWidget>(this, wInventory);
		if (inventory)
		{
			inventory->AddToViewport();
			inventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (wQuickSlot)
	{
		this->quickslot = CreateWidget<UUserWidget>(this, wQuickSlot);
		if (quickslot)
		{
			quickslot->AddToViewport();
			quickslot->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMainplayerController::Tick(float DeltaTime)
{
}

void AMainplayerController::SetVisibleHUD()
{
	if (crosshair)
	{
		UE_LOG(LogTemp, Log, TEXT("set visible hud"));
		this->bCrosshairvisible = true;
		this->crosshair->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainplayerController::SetRemoveHUD()
{
	if (crosshair)
	{
		UE_LOG(LogTemp, Log, TEXT("set remove hud"));
		this->bCrosshairvisible = false;
		this->crosshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainplayerController::SetVisiblePause()
{

}

void AMainplayerController::SetRemovePause()
{

}

void AMainplayerController::SetVisibleQuickSlot()
{

}

void AMainplayerController::SetRemoveQuickSlot()
{

}

