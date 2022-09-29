// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include <string>

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Pull Car from pool to world
void ASpawner::PullCar()
{
	if(CarPool.Num() != 0){
		ACar* CarToPull = CarPool[0];
		CarToPull->OnCarPulled();
		CarToPull->SetActorLocation(this->GetActorLocation());
		CarPool.Remove(CarToPull);
		LastPulledCar = CarToPull;
	}
	else{
		SpawnCar();
	}
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
	PushCar(SpawnedCar);
	PullCar();
}

