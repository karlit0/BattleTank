// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* controlledTank = GetPawn();
	if (!ensure(controlledTank))
		return;

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController))
		return;

	APawn* playerTank = nullptr;
	playerTank = playerController->GetPawn();
	if (!playerTank)
		return;

	UTankAimingComponent* aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent))
		return;

	// Move towards the player
	MoveToActor(playerTank, AcceptanceRadius); // TODO check radius is in cm

	FVector tankForward = controlledTank->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = (playerTank->GetActorLocation() - controlledTank->GetActorLocation()).GetSafeNormal();

	// Aim towards the player
	aimingComponent->AimAt(playerTank->GetActorLocation());
	
	if (aimingComponent->GetFiringState() == EFiringState::Locked)
		aimingComponent->Fire(); // TODO limit firing rate
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* possesedTank = Cast<ATank>(InPawn);
		if (!possesedTank)
		{
			return;
		}

		// Subscribe our local method to the tank's death event
		possesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::OnPossesedTankDeath()
{	
	ATank* possesedTank = Cast<ATank>(GetPawn());
	if (!ensure(possesedTank))
		return;
	
	possesedTank->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("AIController handling Tank Death!"));
}