// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	Speed = 100.f;
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCar(DeltaTime);

}

// Moves car forward
void ACar::MoveCar(float DeltaTime)
{
	FVector CarLocation = this->GetActorLocation();
	FVector CarForwardVector = this->GetActorForwardVector();
	FVector NewLocation = CarLocation + (CarForwardVector * (Speed * DeltaTime));
	this->SetActorLocation(NewLocation);
}

