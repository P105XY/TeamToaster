// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "MainPlayer.h"
#include "Inventory.generated.h"

UCLASS()
class KNN_API AInventory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventory();

	class ItemBase* curItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClearInventory();
	void GetItem(ItemBase* getit);
	void UseItem(ItemBase* usingit);
};
