// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamlineSpawners.h"
#include "MySpawners.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyPoolObject.h"


// Sets default values
AMySpawners::AMySpawners()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Box Component to represent the spwan volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	FVector BoxSize = FVector(90.0f,80.0f,40.0f);
	WhereToSpawn->SetBoxExtent(BoxSize,true);
	RootComponent = WhereToSpawn;
	
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0,0,-(BoxSize.Z/2)));
		SphereVisual->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	}

	CountObject = 0;
}

// Called when the game starts or when spawned
void AMySpawners::BeginPlay()
{
	Super::BeginPlay();
	
	if (CountObject < NumberOfObjectsToSpawn)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &AMySpawners::SpawnPoolObject, SpawnDelay, false);
	}
	
}

// Called every frame
void AMySpawners::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// To get random point within Box Spawner
FVector AMySpawners::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	//return SpawnOrigin;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

// To get random point within Box Spawner
FVector AMySpawners::GetRandomDirection()
{
	FVector NewDirection;
	NewDirection.X = FMath::FRandRange(-360.0f, 360.0f);
	NewDirection.Y = FMath::FRandRange(-360.0f, 360.0f);
	NewDirection.Z = FMath::FRandRange(-360.0f, 360.0f);

	return NewDirection;
}

void AMySpawners::SpawnPoolObject()
{
	// Check if we have something to Spawn
	if (WhatToSpawn != NULL)
	{
		// Check if the world is valid
		UWorld* const World = GetWorld();
		if (World)
		{
			// Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get the center positon within the spawner
			FVector SpawnLocation;
			SpawnLocation = WhereToSpawn->Bounds.Origin;

			if (RandomlySpawn)
			{
				SpawnLocation = GetRandomPointInVolume();
			}
			else
			{
				SpawnLocation = WhereToSpawn->Bounds.Origin;
			}

			// Get the random positon within the spawner
			FVector NewLocation = GetRandomDirection();

			// Get a random rotation for the spawned item
			FRotator SpawnRotator;
			SpawnRotator.Yaw = FMath::FRand() * 360.0f;
			SpawnRotator.Pitch = FMath::FRand() * 360.0f;
			SpawnRotator.Roll = FMath::FRand() * 360.0f;
			FQuat SpawnRotation = FQuat(SpawnRotator);		

			// Set the Location and Rotation into Transform
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);
			SpawnTransform.SetRotation(SpawnRotation);


			// Spawn the pool object

			// to set the timer, when the object need to be destroyed based current lifetime
			float Lifetime = FMath::FRandRange(LifetimeMinimum, LifetimeMaximum);
			// Log a debug message
			FString PickupDebugString = WhatToSpawn->GetName();
			FString CurrentLifetime = FString::SanitizeFloat(WhatToSpawn->GetDefaultObject<AMyPoolObject>()->GetLifetime());
			AMyPoolObject*  const SpawnedPoolObject = World->SpawnActorDeferred<AMyPoolObject>(WhatToSpawn, SpawnTransform);
			SpawnedPoolObject->SetLifetime(Lifetime);
			SpawnedPoolObject->SetNewLocation(NewLocation);
			SpawnedPoolObject->SetVelocity(CurrentVelocity);
			SpawnedPoolObject->FinishSpawning(SpawnTransform);
			
			
			CountObject++;
			if (CountObject < NumberOfObjectsToSpawn)
			{
				GetWorldTimerManager().SetTimer(SpawnTimer, this, &AMySpawners::SpawnPoolObject, SpawnDelay, false);
			}


		}
					
	}
		
}

