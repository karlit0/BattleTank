// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ATank* controlledTank = GetControlledTank();
	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
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
		
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *hitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
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
	// Line-trace along that look direction, and see what we hit (up to max range)

	return ret;
}
