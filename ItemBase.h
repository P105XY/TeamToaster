// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class KNN_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemBase();

	//view in inventory
	UTexture2D* iconImage;
	float currentStack;
	float currentHealing;
	float maxStack;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UsingItem();
};
