// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHair.h"

void ACrossHair::DrawHUD()
{
	AHUD::DrawHUD();

	if (Crosshair)
	{
		FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D crosshairposition(center.X - Crosshair->GetSurfaceWidth() * 0.5f, center.Y - (Crosshair->GetSurfaceHeight() * 0.5f));

		FCanvasTileItem tileitem(crosshairposition, Crosshair->Resource, FLinearColor::White);
		tileitem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(tileitem);
	}
}