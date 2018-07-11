// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetMeshComponents(UTankBarrel* barrel, UTankTurret* turret)
{
	Barrel = barrel;
	Turret = turret;
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
		PointBarrelAt(launchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::PointBarrelAt(FVector const & aimDirection)
{
	const auto barrelRotator = Barrel->GetForwardVector().ToOrientationRotator();
	const auto aimRotator = aimDirection.ToOrientationRotator();
	const auto deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate( deltaRotator.Pitch );
	Turret->Rotate ( deltaRotator.Yaw   );
}