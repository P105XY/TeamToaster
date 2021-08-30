// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerHud.h"
#include "MainPlayer.h"
#include "KNNGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class KNN_API AKNNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKNNGameModeBase();

	AMainPlayer* mainp;
};
