// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Car.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class MYUNREALROAD_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=ObjectPooling)
	TSubclassOf<ACar> CarClass;

	UPROPERTY(BlueprintReadOnly, Category=ObjectPooling)
	ACar* LastPulledCar;

	// Pull Car from pool to world
	UFUNCTION(BlueprintCallable, Category = "ObjectPooling")
	void PullCar();

	// Push car from world to pool
	UFUNCTION(BlueprintCallable, Category = "ObjectPooling")
	void PushCar(ACar* CarToPush);

private:
	// Amount of cars already spawned by this spawner
	int SpawnedCars;

	// Spawns additional car
	void SpawnCar();

	//Main car pool
	UPROPERTY()
	TArray<ACar*> CarPool;
};
