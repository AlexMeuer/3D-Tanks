// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrel(UTankBarrel* barrel)
{
	Barrel = barrel;
}

void UTankAimingComponent::AimAt(FVector const & hitLocation, float launchSpeed)
{
	if (!Barrel) { return; }

	const FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	FVector launchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,	// Favor lower arc
		0.0f,	// No collision radius
		0.0f,	// No gravity override
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		const FVector aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No aiming solution."))
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector const & aimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	const FRotator barrelRotation = Barrel->GetForwardVector().Rotation();
	const FRotator aimRotator = aimDirection.Rotation();
	const FRotator deltaRotator = aimRotator - barrelRotation;
	
	Barrel->Elevate(5.0f);
}