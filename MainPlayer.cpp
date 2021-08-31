// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 3;
	maxstamina = 100.f;
	stamina = maxstamina;
	attackdamage = 10.f;
	walkspeed = 300.f;
	battlespeed = 250.f;
	runningspeed = 400.f;

	normallength = 500.f;
	runninglength = 600.f;
	currentlength = normallength;

	bisattacking = false;
	bisrunning = false;
	bmoveforward = false;
	bmoveright = false;
	bisbattle = false;

	camArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamArm"));
	agroBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AgroBox"));
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));

	camArm->SetupAttachment(GetRootComponent());
	camArm->TargetArmLength = currentlength;
	camArm->bUsePawnControlRotation = true;

	cam->SetupAttachment(camArm, USpringArmComponent::SocketName);
	cam->bUsePawnControlRotation = false;


	battleCamLoc = FVector(120.f, 140.f, 80.f);
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	pcon = Cast<AMainplayerController>(GetController());

	playerstatus = EPlayerStatus::EPS_Idle;
	playercondition = EPlayerCondition::EPC_Normal;
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerSwitchLookatFront();
	GetLiteralSpeed();
}
// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//action value
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainPlayer::Attack);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AMainPlayer::BlockDown);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AMainPlayer::BlockUp);
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AMainPlayer::EvadeUp);
	PlayerInputComponent->BindAction("Evade", IE_Released, this, &AMainPlayer::EvadeUp);
	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AMainPlayer::LockOnDown);
	PlayerInputComponent->BindAction("LockOn", IE_Released, this, &AMainPlayer::LockOnUp);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainPlayer::SprintDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainPlayer::SprintUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AMainPlayer::MoveSide);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookSide", this, &AMainPlayer::LookSide);
}

void AMainPlayer::MoveForward(float value)
{
	this->bmoveforward = false;
	if (CanMove(value))
	{
		this->bmoveforward = true;
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yawrot(0.f, rot.Yaw, 0.f);
		const FVector direction = FRotationMatrix(yawrot).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AMainPlayer::MoveSide(float value)
{
	this->bmoveright = false;
	if (CanMove(value))
	{
		this->bmoveright = true;
		const FRotator rot = Controller->GetControlRotation();
		const FRotator yawrot(0.f, rot.Yaw, 0.f);
		const FVector direction = FRotationMatrix(yawrot).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, value);
	}
}

void AMainPlayer::LookUp(float value)
{
	if (value != 0.f)
	{
		AddControllerPitchInput(value);
	}
}

void AMainPlayer::LookSide(float value)
{
	if (value != 0.f)
		AddControllerYawInput(value);
}

void AMainPlayer::Attack()
{
}

void AMainPlayer::SprintDown()
{

}

void AMainPlayer::SprintUp()
{

}

void AMainPlayer::BlockDown()
{
}

void AMainPlayer::BlockUp()
{
}

void AMainPlayer::EvadeDown()
{

}

void AMainPlayer::EvadeUp()
{
}

void AMainPlayer::LockOnDown()
{
	bisbattle = !bisbattle;

	bUseControllerRotationYaw = bisbattle;
	bUseControllerRotationRoll = bisbattle;
	GetCharacterMovement()->bOrientRotationToMovement = !bisbattle;

	if (bisbattle)
	{
		SettingPlayerStatus(EPlayerStatus::EPS_Battle);
		pcon->SetVisibleHUD();
		cam->FieldOfView = 80.f;
	}
	else if (!bisbattle)
	{
		SettingPlayerStatus(EPlayerStatus::EPS_Idle);
		pcon->SetRemoveHUD();
		cam->FieldOfView = 100.f;
	}
}

void AMainPlayer::LockOnUp()
{

}

void AMainPlayer::GetLiteralSpeed()
{
	FVector curspeed = this->GetVelocity();
	FVector literalSpeed = FVector(curspeed.X, curspeed.Y, 0.f);
	currentSpeed = literalSpeed.Size();
}

static FRotator* curRot;
static FVector* curLoc;

void AMainPlayer::PlayerSwitchLookatFront()
{
	curRot = new FRotator(GetControlRotation());
	curLoc = new FVector(camArm->GetRelativeLocation());
	if (bisbattle)
	{
		this->SetActorRotation(FRotator(0.f, FMath::FInterpTo(GetActorRotation().Yaw, curRot->Yaw, GetWorld()->DeltaTimeSeconds, 0.7f), 0.f));
		this->camArm->SetRelativeLocation(FVector(FMath::VInterpTo(camArm->GetRelativeLocation(), FVector(120.f, 140.f, 80.f), GetWorld()->GetDeltaSeconds(), 12.0f)));
	}
	if (!bisbattle)
	{
		camArm->SetRelativeLocation(FMath::VInterpTo(camArm->GetRelativeLocation(), FVector::ZeroVector, GetWorld()->GetDeltaSeconds(), 12.f));
	}

}

bool AMainPlayer::CanMove(float value)
{
	return (Controller != nullptr) &&
		(value != 0.f) &&
		(this->playerstatus != EPlayerStatus::EPS_Death);
}

