// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAniminstance.h"

void UPlayerAniminstance::UpdateAnimation()
{
	if (!playerpawn)
	{
		playerpawn = TryGetPawnOwner();
		if (playerpawn)
		{
			playerpawn = Cast<AMainPlayer>(playerpawn);
		}
	}
}

UPlayerAniminstance::UPlayerAniminstance()
{
}