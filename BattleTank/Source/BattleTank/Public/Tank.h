// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	ATank();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
