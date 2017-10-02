// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	ATank* GetControlledTank() const;
	// Start the tank moving the barrel so that a shot would hit where
	// the cross-hair intersects the world
	void AimTowardsCrosshair();

	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

private:
	UPROPERTY(EditAnywhere)
	float	CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float	CrossHairYLocation = 0.33333f;

};