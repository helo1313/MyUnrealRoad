// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"

#include "DrawDebugHelpers.h"

// Sets default values
ACar::ACar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 100.f;
	CalculateSpeedChangeStrength();
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	OnCarPulled();
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CalculateCarBehavior())
	{
	case EmergencyBraking:
		ChangeCarSpeed(SpeedChangeStrength * -10,DeltaTime);
		break;	
	case SlowDown:
		ChangeCarSpeed(SpeedChangeStrength * -1,DeltaTime);
		break;
	case Idle:
		break;
	case SpeedUp:
		ChangeCarSpeed(SpeedChangeStrength ,DeltaTime);
		break;
	}

	MoveCar(DeltaTime);

}

// Triggered by spawner when car is pulled to queue
void ACar::OnCarPushed()
{
	SetActorHiddenInGame(true);
	SetActorLocation(FVector(0,0,0));
	SetActorTickEnabled(false);
}

// Triggered by spawner when car is pulled to world
void ACar::OnCarPulled()
{
	MaxSpeed = FMath::RandRange(MinimalSpeedRange, MaximumSpeedRange);
	Speed = 100.f;
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}

void ACar::CalculateSpeedChangeStrength()
{
	float SpeedRange = MaximumSpeedRange - MinimalSpeedRange;
	SpeedChangeStrength = SpeedRange/4;
}

// Moves car forward
void ACar::MoveCar(float DeltaTime)
{
	FVector CarLocation = this->GetActorLocation();
	FVector CarForwardVector = this->GetActorForwardVector();
	FVector NewLocation = CarLocation + (CarForwardVector * (Speed * DeltaTime));
	this->SetActorLocation(NewLocation);
}

EAccelerationMode ACar::CalculateCarBehavior()
{
	//Trace what is in front of the car
	FHitResult OutHit;
	FVector Start = this->GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * SafeDistance);
	FCollisionQueryParams TraceParameters;
	TraceParameters.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,TraceParameters);

	//Handle behvior base on trace result
	if(OutHit.bBlockingHit){
		ACar* HitCar = Cast<ACar>(OutHit.Actor);
		if (HitCar && HitCar->Speed < this->Speed)
		{
			if(OutHit.Distance > 300){
				return SlowDown;
			}
			else{
				return EmergencyBraking;
			}
		}
		else{
			return Idle;
		}
	}
	else{
		if (Speed < MaxSpeed){
			return SpeedUp;
		}
		else{
			return Idle;
		}
	}
}

// Change car speed base on SpeedChangeValue
void ACar::ChangeCarSpeed(float SpeedChangeValue, float DeltaTime)
{
	float NewSpeed = Speed + (DeltaTime * SpeedChangeValue);
	Speed = FMath::Clamp(NewSpeed, 0.f, MaxSpeed);
}

