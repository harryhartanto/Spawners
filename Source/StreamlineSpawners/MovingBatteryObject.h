// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyPoolObject.h"
#include "MovingBatteryObject.generated.h"

/**
 * 
 */
UCLASS()
class STREAMLINESPAWNERS_API AMovingBatteryObject : public AMyPoolObject
{
	GENERATED_BODY()

public:
		AMovingBatteryObject();	

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Tick(float DeltaSeconds) override;
		
		FVector CurrentLocation;
private:
	float Speed;
};
