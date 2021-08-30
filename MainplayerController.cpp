// Fill out your copyright notice in the Description page of Project Settings.


#include "MainplayerController.h"

AMainplayerController::AMainplayerController()
{

}

void AMainplayerController::BeginPlay()
{
	if (wCrosshair)
	{
		this->crosshair = CreateWidget<UUserWidget>(this, wCrosshair);
	}
	crosshair->AddToViewport();
	crosshair->SetVisibility(ESlateVisibility::Hidden);
}

void AMainplayerController::Tick(float DeltaTime)
{
}

void AMainplayerController::SetVisibleHUD()
{
	this->crosshair->SetVisibility(ESlateVisibility::Visible);
}

void AMainplayerController::SetRemoveHUD()
{
	this->crosshair->SetVisibility(ESlateVisibility::Hidden);
}

