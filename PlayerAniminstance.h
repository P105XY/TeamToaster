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
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void UpdateAnimation();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AMainPlayer* mainplayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class APawn* playerpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator playerrot;
};
