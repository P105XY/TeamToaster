// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayer.h"
#include "Components/PoseableMeshComponent.h"
#include "PlayerAniminstance.generated.h"

/**
 *
 */
UCLASS()
class KNN_API UPlayerAniminstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAniminstance();

	UFUNCTION(BlueprintCallable)
		void UpdateAnimation();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AMainPlayer* mainplayer;
	UPROPERTY(VisibleAnywhere)
		class APawn* playerpawn;
	UPROPERTY(EditAnywhere)
		float currerntRotPitch;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bcurrentPlayerInBattle;
};
