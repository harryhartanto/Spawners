// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MySpawners.generated.h"

UCLASS()
class STREAMLINESPAWNERS_API AMySpawners : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpawners();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/* Return the WhereToSpawn subobject*/
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomDirection();

protected:
	
	/* The pool object to be spawned*/
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AMyPoolObject> WhatToSpawn;

	FTimerHandle SpawnTimer;

	/* The flag to decide where to spawn, true in the center otherwise will be spawn randomly */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool RandomlySpawn;

	/* The speed of the objects to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float CurrentVelocity;

	/* Minimum of the lifetime of the object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float LifetimeMinimum;

	/* Maximum of the lifetime of the object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float LifetimeMaximum;

	/* The number of objects to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 NumberOfObjectsToSpawn;

	/* The number of objects to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelay;
	

private:
	
	/* Box Component to specify where the object need to be spawned*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;	

	 /* Function to spawn the object */
	void SpawnPoolObject();

	int32 CountObject;
};
