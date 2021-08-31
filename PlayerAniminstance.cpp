// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAniminstance.h"

void UPlayerAniminstance::NativeInitializeAnimation()
{
	if (playerpawn == nullptr)
		playerpawn = TryGetPawnOwner();
}

void UPlayerAniminstance::NativeBeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("Begin Native play"));
	if (playerpawn == nullptr)
		playerpawn = TryGetPawnOwner();
	if (playerpawn != nullptr)
	{
		mainplayer = Cast<AMainPlayer>(playerpawn);
	}
}

void UPlayerAniminstance::UpdateAnimation()
{
	if (!playerpawn) { playerpawn = TryGetPawnOwner(); }
	if (playerpawn)
	{
		mainplayer = Cast<AMainPlayer>(playerpawn);
	}
}

UPlayerAniminstance::UPlayerAniminstance()
{
}