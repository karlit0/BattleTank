// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();	
	UTankAimingComponent* aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (aimingComponent)
	{
		FoundAimingComponent(aimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find aiming component at Begin Play"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	ATank* tank = Cast<ATank>(GetPawn());
	return tank;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector hitLocation; // Out parameter
	if (GetSightRayHitLocation(hitLocation)) // Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(hitLocation);
	}
}

// Get world location of line-trace through cross-hair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	bool ret = true;

	// Find the cross-hair position in pixel coordinates
	int32 viewPortSizeX;
	int32 viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	FVector2D screenLocation = FVector2D(viewPortSizeX * CrossHairXLocation, viewPortSizeY * CrossHairYLocation);

	// "De-project" the screen position of the cross-hair to a world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(lookDirection, LineTraceRange, OutHitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *OutHitLocation.ToString());
	}


	return ret;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	bool ret = false;

	FVector cameraWorldLocation; // To be discarded
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, OutLookDirection))
	{
		ret = true;
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *OutLookDirection.ToString());
	}

	return ret;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, float LineTraceRange, FVector& OutHitLocation) const
{
	bool ret = false;

	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(
			hitResult,
			startLocation, 
			startLocation + LineTraceRange * LookDirection,
			ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = hitResult.Location;
		ret = true;
	}
	else
	{
		OutHitLocation = FVector(0.f);
	}
	

	return ret;
}
