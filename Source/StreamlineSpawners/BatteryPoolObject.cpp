// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamlineSpawners.h"
#include "BatteryPoolObject.h"


ABatteryPoolObject::ABatteryPoolObject()
{
	GetMesh()->SetSimulatePhysics(true);
}
