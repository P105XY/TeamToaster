// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackEndNotify.h"

FString UEnemyAttackEndNotify::GetNotifyName_Implementation() const
{
	return "AttackEnd";
}

void UEnemyAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AEnemyBase* enemy = Cast<AEnemyBase>(MeshComp->GetOwner());
	if (enemy != nullptr)
	{
		enemy->AttackEnd();
	}
}
