// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = nullptr;
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (ensure(playerController))
	{
		playerTank = Cast<ATank>(playerController->GetPawn());
	}

	if (ensure(controlledTank) && ensure(playerTank))
	{
		// Move towards the player
		MoveToActor(playerTank, AcceptanceRadius); // TODO check radius is in cm

		FVector tankForward = controlledTank->GetActorForwardVector().GetSafeNormal();
		FVector AIForwardIntention = (playerTank->GetActorLocation() - controlledTank->GetActorLocation()).GetSafeNormal();

		// Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		controlledTank->Fire(); // TODO limit firing rate
	}
}

