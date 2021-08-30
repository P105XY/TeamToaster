// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	movespeed = 250.f;
	attackdamage = 10.f;
	attackdelay = 3.f;
	targetingrange = 600.f;
	attackrange = 80.f;

	agro = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	target = CreateDefaultSubobject<USphereComponent>(TEXT("TargetSphere"));
	attackcollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));

	agro->SetSphereRadius(this->targetingrange);
	target->SetSphereRadius(this->attackrange);

	agro->SetupAttachment(GetRootComponent());
	target->SetupAttachment(GetRootComponent());
	attackcollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("AttackSocket"));

	SetCurrentStatus(EEnemyStatus::EES_Idle);

	GetCharacterMovement()->MaxWalkSpeed = movespeed;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	aicontroller = Cast<AAIController>(this->GetController());

	agro->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAgroBegin);
	target->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnTargetBegin);
	attackcollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAttackCollisionBegin);

	agro->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnAgroEnd);
	target->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnTargetEnd);
	attackcollision->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnAttackCollisionEnd);

	agro->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	target->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	attackcollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	agro->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	target->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	attackcollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	attackcollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bisattack = false;
	bisdead = false;
	player = nullptr;

	GetWorld()->GetTimerManager().ClearTimer(attackTimer);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector movedirec = GetVelocity();
	currentspeed = movedirec.Size();
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::OnAgroBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		player = Cast<AMainPlayer>(OtherActor);
		if (player)
		{
			MoveToTarget(player);
		}
	}

}

void AEnemyBase::OnTargetBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		player = Cast<AMainPlayer>(OtherActor);
		if (player)
		{
			Attack();
		}
	}
}

void AEnemyBase::OnAttackCollisionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AEnemyBase::OnAgroEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		player = Cast<AMainPlayer>(OtherActor);
		if (player)
		{
			aicontroller->StopMovement();
			GetWorld()->GetTimerManager().ClearTimer(attackTimer);

		}
		SetCurrentStatus(EEnemyStatus::EES_Idle);
	}
}

void AEnemyBase::OnTargetEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		player = Cast<AMainPlayer>(OtherActor);
		if (player)
		{
			GetWorld()->GetTimerManager().ClearTimer(attackTimer);
			MoveToTarget(player);
		}
	}
}

void AEnemyBase::OnAttackCollisionEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//null
}

void AEnemyBase::MoveToTarget(AMainPlayer* tg)
{
	if (!bisattack && !bisdead)
	{
		UE_LOG(LogTemp, Log, TEXT("movetotarget"));
		SetCurrentStatus(EEnemyStatus::EES_Move);

		FAIMoveRequest movereq;

		movereq.SetGoalActor(tg);
		movereq.SetAcceptanceRadius(20.f);

		FNavPathSharedPtr path;
		this->aicontroller->MoveTo(movereq, &path);
	}
}

void AEnemyBase::Attack()
{
	if (!bisattack)
	{
		UE_LOG(LogTemp, Log, TEXT("Attack calling"));
		SetCurrentStatus(EEnemyStatus::EES_Attack);
		bisattack = true;
		attackMotion = FMath::RandRange(1, 3);

		UAnimInstance* animinst = GetMesh()->GetAnimInstance();

		if (animinst)
		{
			animinst->Montage_Play(animmontage, 1.0f);
			switch (attackMotion)
			{
			case 1:
				animinst->Montage_JumpToSection(FName("Attack01"), animmontage);
				break;
			case 2:
				animinst->Montage_JumpToSection(FName("Attack02"), animmontage);
				break;
			case 3:
				animinst->Montage_JumpToSection(FName("Attack03"), animmontage);
				break;
			default:
				break;
			}
		}
	}
}

void AEnemyBase::AttackEnd()
{
	this->bisattack = false;
	GetWorld()->GetTimerManager().SetTimer(attackTimer, this, &AEnemyBase::Attack, attackdelay, false);
}

void AEnemyBase::Death()
{
	this->bisdead = false;
}

void AEnemyBase::DeathEnd()
{

}

