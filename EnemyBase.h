// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "MainPlayer.h"
#include "AIController.h"
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyStatus : uint8
{
	EES_Idle UMETA(DisplayName = "Idle"),
	EES_Move UMETA(DisplayName = "Move"),
	EES_Sprint UMETA(DisplayName = "Sprint"),
	EES_Attack UMETA(DisplayName = "Attack"),
	EES_Death UMETA(DisplayName = "Death"),
	EES_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class KNN_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	float movespeed;
	float attackdamage;
	float attackdelay;
	float targetingrange;
	float attackrange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "animation")
		float currentspeed;
	int attackMotion;

	bool bisattack;
	bool bisdead;

	class USphereComponent* agro;
	class USphereComponent* target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP")
		class UBoxComponent* attackcollision;
	class AMainPlayer* player;
	class AAIController* aicontroller;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "animation")
		class UAnimMontage* animmontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "status")
		EEnemyStatus currentStatus;

	FTimerHandle attackTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//collision
	UFUNCTION()
		void OnAgroBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnTargetBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackCollisionBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnAgroEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnTargetEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnAttackCollisionEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	//inline
	FORCEINLINE void SetCurrentStatus(EEnemyStatus st) { this->currentStatus = st; }
	FORCEINLINE EEnemyStatus GetCurrentStatus() { return this->currentStatus; }

	void MoveToTarget(AMainPlayer* tg);
	void Attack();
	void AttackEnd();
	void Death();
	void DeathEnd();
};
