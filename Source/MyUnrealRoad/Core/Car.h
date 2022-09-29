// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.generated.h"

UENUM()
enum EAccelerationMode
{
	EmergencyBraking    UMETA(DisplayName = "EmergencyBraking"),
	SlowDown			UMETA(DisplayName = "SlowDown"),
	Idle				UMETA(DisplayName = "Idle"),
	SpeedUp				UMETA(DisplayName = "SpeedUp"),
  };

UCLASS()
class MYUNREALROAD_API ACar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Triggered by spawner when car is pushed to world
	void OnCarPushed();
	// Triggered by spawner when car is pulled from world 
	void OnCarPulled();

	// Minimal speed that can be drawn as MaxSpeed when car is spawned 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Speed")
	float MinimalSpeedRange = 100.f;

	// Maximum speed that can be drawn as MaxSpeed when car is spawned 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Speed")
	float MaximumSpeedRange = 500.f;

	// Strenght of speed change
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float SpeedChangeStrength = 100.f;

	// Distance that car will try to keep from other car
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float SafeDistance = 600.f;
	
	// Current car speed
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float Speed = 0.f;

	// Maximum possible car speed 
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float MaxSpeed = 0.f;

private:
	// Calculate speed change strength base on minimal and maximal speed range
	void CalculateSpeedChangeStrength();
	
	// Moves car forward
	void MoveCar(float DeltaTime);

	// Calculates if car should speed up or break down
	EAccelerationMode CalculateCarBehavior();

	// Change car speed base on SpeedChangeValue
	void ChangeCarSpeed(float SpeedChangeValue ,float DeltaTime);
	
};
