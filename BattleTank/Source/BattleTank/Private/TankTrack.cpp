// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp actual throttle value so player can't over-drive
	FVector forceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


