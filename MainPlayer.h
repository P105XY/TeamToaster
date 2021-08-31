// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "Components/PoseableMeshComponent.h"
#include "MainplayerController.h"
#include "Engine/SkeletalMesh.h"
#include "PlayerHud.h"
#include "MainPlayer.generated.h"

UENUM(BlueprintType)
enum class EPlayerCondition : uint8
{
	EPC_Normal UMETA(DisplayName = "Normal"),
	EPC_Bleeding UMETA(DisplayName = "Bleeding"),
	EPC_BrokenBone UMETA(DisplayName = "BrokenBone"),
	EPC_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EPlayerStatus : uint8
{
	EPS_Idle UMETA(DisplayName = "Idle"),
	EPS_Move UMETA(DisplayName = "Move"),
	EPS_Sprint UMETA(DisplayName = "Sprint"),
	EPS_Attack UMETA(DisplayName = "Attack"),
	EPS_Evade UMETA(DisplayName = "Evade"),
	EPS_Battle UMETA(DisplayName = "Battle"),
	EPS_Death UMETA(DisplayName = "Death"),
	EPS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class KNN_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMainPlayer();

	//mainplayer variable
	float health;
	float maxstamina, stamina;
	float walkspeed, battlespeed, runningspeed;
	float attackdamage;
	float currentlength, runninglength, normallength;
	UPROPERTY(EditAnywhere)
		float turnrot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float currentSpeed;

	bool bisattacking;
	bool bisrunning;
	bool bmoveforward;
	bool bmoveright;
	bool bisbattle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerStatus playerstatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerCondition playercondition;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* camArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		class UBoxComponent* agroBox;

	class UCameraComponent* cam;

	class AMainplayerController* pcon;

	UPROPERTY(VisibleAnywhere)
		TArray<UCameraComponent*> Cams;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* sktlMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APlayerHud* phud;

	FVector battleCamLoc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//inline functions
	FORCEINLINE void SettingPlayerStatus(EPlayerStatus st) { this->playerstatus = st; }
	FORCEINLINE EPlayerStatus GettingPlayerStatus() { return this->playerstatus; }

	//functions
	void MoveForward(float value);
	void MoveSide(float value);
	void LookUp(float value);
	void LookSide(float value);

	//action functions
	void Attack();
	void SprintDown();
	void SprintUp();
	void BlockDown();
	void BlockUp();
	void EvadeDown();
	void EvadeUp();
	void LockOnDown();
	void LockOnUp();
	void PlayerSwitchLookatFront();
	void GetLiteralSpeed();
	void IncreaseHealth(float healingamount);
	void DecreaseHealth(float damageamount);
	//return value functions
	bool CanMove(float value);
};