// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyBase.h"
#include "EnemyBaseAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class KNN_API UEnemyBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//애니메이션 헤더는 생성자나 beginplay 대신 nativeinitializeanimation으로 생성함.
	virtual void NativeInitializeAnimation() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "animation")
		class AEnemyBase* enemy;
	class APawn* pawn;
};
