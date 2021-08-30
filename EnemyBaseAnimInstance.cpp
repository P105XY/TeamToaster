// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseAnimInstance.h"

void UEnemyBaseAnimInstance::NativeInitializeAnimation()
{
	if (pawn == nullptr)
	{
		pawn = TryGetPawnOwner();
		if (pawn != nullptr)
		{
			enemy = Cast<AEnemyBase>(pawn);
		}
	}
}