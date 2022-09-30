// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Pull Car from pool to world
void ASpawner::PullCar()
{
	if (CarPool.Num() == 0)
	{
		SpawnCar();
		return;
	}
	
	ACar* CarToPull = CarPool[0];
	if (!IsValid(CarToPull))
	{
		return;
	}
	CarToPull->OnCarPulled();
	CarToPull->SetActorLocation(this->GetActorLocation());
	CarPool.Remove(CarToPull);
	LastPulledCar = CarToPull;
}

// Push car from world to pool
void ASpawner::PushCar(ACar* CarToPush)
{
	CarToPush->OnCarPushed();
	CarPool.AddUnique(CarToPush);
}

// Spawns additional car
void ASpawner::SpawnCar()
{
	ACar* SpawnedCar = Cast<ACar>(GetWorld()->SpawnActor(CarClass));
	if (!IsValid(SpawnedCar))
	{
		return;
	}
	PushCar(SpawnedCar);
	PullCar();
}
