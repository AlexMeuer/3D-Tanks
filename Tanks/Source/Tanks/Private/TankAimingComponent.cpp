// Copyright Alexander Meuer

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* barrel, UTankTurret* turret, UParticleSystemComponent* muzzleFlash)
{
	Barrel = barrel;
	Turret = turret;
	MuzzleFlash = muzzleFlash;
}

void UTankAimingComponent::AimAt(FVector const & hitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	const FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	FVector launchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		LaunchSpeed,
		false,	// Favor lower arc
		0.0f,	// No collision radius
		0.0f,	// No gravity override
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		PointBarrelAt(launchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (IsReloaded())
	{
		
		const FName socketName("Projectile");

		const auto projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(socketName),
		Barrel->GetSocketRotation(socketName)
		);

		projectile->Launch(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();

		if (MuzzleFlash)
		{
			MuzzleFlash->ActivateSystem();
		}
	}
}

void UTankAimingComponent::PointBarrelAt(FVector const & aimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	const auto barrelRotator = Barrel->GetForwardVector().Rotation();
	const auto aimRotator = aimDirection.Rotation();
	const auto deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate( deltaRotator.Pitch );
	Turret->Rotate ( deltaRotator.Yaw   );
}

bool UTankAimingComponent::IsReloaded() const
{
	return (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
}