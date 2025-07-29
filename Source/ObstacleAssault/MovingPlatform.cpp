// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
	FString Name = GetName(); // "My String Value";
	//converting operator (*) needed for the string
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call base class tick

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if (ShouldPlatformReturn()) 
	{
		// float OverShoot = DistanceMoved - MoveDistance;
		// FString PlatformName = GetName();
		// UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by: %f"), *PlatformName,OverShoot);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// prevent drifted beginning, begin from where the platform should have been
		StartLocation = StartLocation + (MoveDirection * MoveDistance); 
		SetActorLocation(StartLocation);
		PlatformVelocity = - PlatformVelocity;
	} 
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity*DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	FString RotationString = CurrentRotation.ToCompactString(); // or ToString()
	// FVector CurrentRotation = GetActorForwardVector();
	// FString PlatformName = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s Platform rotation is: %s"), *GetName(),*RotationString);


}

bool AMovingPlatform::ShouldPlatformReturn()
{
	return GetDistanceMoved() >= MoveDistance;
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}