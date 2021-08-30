// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHud.h"

APlayerHud::APlayerHud()
{

}

void APlayerHud::VisibleHUD()
{
	bShowHUD = true;
}

void APlayerHud::HideHUD()
{
	bShowHUD = false;
}

void APlayerHud::DrawHUD()
{

	AHUD::DrawHUD();

	if (currentCrosshair != nullptr)
	{
		FVector2D centor(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D crosshairPosition(centor.X - currentCrosshair->GetSurfaceWidth() * 0.5f, centor.Y - currentCrosshair->GetSurfaceHeight() * 0.5f);

		FCanvasTileItem tileitem(crosshairPosition, currentCrosshair->Resource, FLinearColor::Black);
		Canvas->DrawItem(tileitem);
	}
}