// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyPoolObject.generated.h"

UCLASS()
class STREAMLINESPAWNERS_API AMyPoolObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPoolObject();

	// Sets default values for this actor's properties with Initial Lifetime
	AMyPoolObject(float IntialLifetime);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/* Return the mesh for MyPoolObject*/
	FORCEINLINE class UStaticMeshComponent* GetMesh()  const { return MyPoolObjectMesh; }

	FTimerHandle LifetimeTimer;

	/* Funtion to call when the object's Lifetime is up*/
	UFUNCTION(BluePrintNativeEvent)
	void TimeIsUp();
	virtual void TimeIsUp_Implementation();


	/* Set the maximum lifetime of the object*/
	UFUNCTION(BlueprintCallable, Category = "PoolObject")
	void SetLifetime(float Lifetime);

	/* Set the maximum lifetime of the object*/
	UFUNCTION(BlueprintPure, Category = "PoolObject")
	float GetLifetime();

	UFUNCTION(BlueprintPure, Category = "PoolObject")
	FVector GetNewLocation();

	UFUNCTION(BlueprintCallable, Category = "PoolObject")
	void SetNewLocation(FVector NewLocation);

	UFUNCTION(BlueprintPure, Category = "PoolObject")
	float GetCurrentVelocity();

	UFUNCTION(BlueprintCallable, Category = "PoolObject")
	void SetVelocity(float NewVelocity);

private:
	/* Static mesh to represent the pickup in the level*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyPoolObject", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MyPoolObjectMesh;

	/* The current Lifetime of the object*/
	float Lifetime;

	FVector NewLocation;

	float Velocity;
};
