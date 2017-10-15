// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

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
	if (playerController)
	{
		playerTank = Cast<ATank>(playerController->GetPawn());
	}

	if (controlledTank && playerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		controlledTank->AimAt(playerTank->GetActorLocation());

		controlledTank->Fire(); // TODO limit firing rate
	}
}

