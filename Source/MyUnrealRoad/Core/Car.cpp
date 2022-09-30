// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

#include "DrawDebugHelpers.h"

// Sets default values
ACar::ACar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = MinimalSpeedRange;
	CalculateSpeedChangeStrength();
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CalculateCarBehavior())
	{
	case EmergencyBraking:
		ChangeCarSpeed(SpeedChangeStrength * -10, DeltaTime);
		break;
	case SlowDown:
		ChangeCarSpeed(SpeedChangeStrength * -1, DeltaTime);
		break;
	case Idle:
		break;
	case SpeedUp:
		ChangeCarSpeed(SpeedChangeStrength, DeltaTime);
		break;
	}

	MoveCar(DeltaTime);
}

// Triggered by spawner when car is pulled to list
void ACar::OnCarPushed()
{
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0, 0, 0));
	SetActorTickEnabled(false);
}

// Triggered by spawner when car is pulled to world
void ACar::OnCarPulled()
{
	MaxSpeed = FMath::RandRange(MinimalSpeedRange, MaximumSpeedRange);
	Speed = MinimalSpeedRange;
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}

void ACar::CalculateSpeedChangeStrength()
{
	const float SpeedRange = MaximumSpeedRange - MinimalSpeedRange;
	SpeedChangeStrength = SpeedRange / 4;
}

// Moves car forward
void ACar::MoveCar(float DeltaTime)
{
	const FVector CarLocation = this->GetActorLocation();
	const FVector CarForwardVector = this->GetActorForwardVector();
	const FVector NewLocation = CarLocation + (CarForwardVector * (Speed * DeltaTime));
	this->SetActorLocation(NewLocation);
}

EAccelerationMode ACar::CalculateCarBehavior() const
{
	//Trace what is in front of the car
	FHitResult OutHit;
	const FVector Start = this->GetActorLocation();
	const FVector End = Start + (GetActorForwardVector() * SafeDistance);
	FCollisionQueryParams TraceParameters;
	TraceParameters.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, TraceParameters);

	//Handle behavior base on trace result
	if (OutHit.bBlockingHit)
	{
		const ACar* HitCar = Cast<ACar>(OutHit.Actor);
		if (IsValid(HitCar) && HitCar->Speed < this->Speed)
		{
			if (OutHit.Distance < 300)
			{
				return EmergencyBraking;
			}
			return SlowDown;
		}
		return Idle;
	}
	
	if (Speed < MaxSpeed)
	{
		return SpeedUp;
	}
	return Idle;
}

// Change car speed base on SpeedChangeValue
void ACar::ChangeCarSpeed(float SpeedChangeValue, float DeltaTime)
{
	float NewSpeed = Speed + (DeltaTime * SpeedChangeValue);
	Speed = FMath::Clamp(NewSpeed, 0.f, MaxSpeed);
}
