// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamlineSpawners.h"
#include "MyPoolObject.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyPoolObject::AMyPoolObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the static mesh component
	MyPoolObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyPoolObjectMesh"));
	RootComponent = MyPoolObjectMesh;
}

// Sets default values with InitialLifetime
AMyPoolObject::AMyPoolObject(float InitialLifetime)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetLifetime(InitialLifetime);
	// Create the static mesh component
	MyPoolObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyPoolObjectMesh"));
	RootComponent = MyPoolObjectMesh;


}

// Called when the game starts or when spawned
void AMyPoolObject::BeginPlay()
{
	Super::BeginPlay();
	// Log a debug message
	FString PickupDebugString = GetName();
	FString CurrentLifetime = FString::SanitizeFloat(Lifetime);
	UE_LOG(LogClass, Log, TEXT("The %s has been spawned"), *PickupDebugString);
	UE_LOG(LogClass, Log, TEXT("The current lifetime :  %s"), *CurrentLifetime);
	// Time is up
	GetWorldTimerManager().SetTimer(LifetimeTimer, this, &AMyPoolObject::TimeIsUp_Implementation, Lifetime, false);
}

// Called every frame
void AMyPoolObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// To destroy the object when the lifetime is up
void AMyPoolObject::TimeIsUp_Implementation()
{
	// Log a debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("The %s has been destroyed"), *PickupDebugString);
	Destroy();
}

// Set the Lifetime
void AMyPoolObject::SetLifetime(float CurrentLifespan)
{
	Lifetime = CurrentLifespan;
}


// Return the current Lifetime
float AMyPoolObject::GetLifetime()
{
	return Lifetime;
}

// Return the new location
FVector AMyPoolObject::GetNewLocation()
{
	return NewLocation;
}

// Set the new location
void AMyPoolObject::SetNewLocation(FVector Location)
{
	NewLocation = Location;
}

// Return the Velocity
float AMyPoolObject::GetCurrentVelocity()
{
	return Velocity;
}

// Set the new Velocity
void AMyPoolObject::SetVelocity(float NewVelocity)
{
	Velocity = NewVelocity;
}

