// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Car.generated.h"

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

	// Current car speed
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float Speed = 0.f;

	// Maximum possible car speed 
	UPROPERTY(BlueprintReadOnly, Category = "Speed")
	float MaxSpeed = 0.f;

private:
	// Moves car forward
	void MoveCar(float DeltaTime);

};
