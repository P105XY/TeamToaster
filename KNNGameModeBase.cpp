// Copyright Epic Games, Inc. All Rights Reserved.


#include "KNNGameModeBase.h"

AKNNGameModeBase::AKNNGameModeBase()
{
	HUDClass = APlayerHud::StaticClass();
	DefaultPawnClass = AMainPlayer::StaticClass();

	mainp = Cast<AMainPlayer>(DefaultPawnClass);
}