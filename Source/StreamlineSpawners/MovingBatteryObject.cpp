// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamlineSpawners.h"
#include "MovingBatteryObject.h"


AMovingBatteryObject::AMovingBatteryObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingBatteryObject::BeginPlay()
{
	Super::BeginPlay();
	Speed = GetCurrentVelocity();
}

// Called every frame
void AMovingBatteryObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentLocation = this->GetActorLocation();
	CurrentLocation.X += GetNewLocation().X * DeltaTime * Speed;
	CurrentLocation.Y += GetNewLocation().Y * DeltaTime * Speed;
	CurrentLocation.Z += GetNewLocation().Z * DeltaTime * Speed;
	
	SetActorLocation(CurrentLocation);	

}
