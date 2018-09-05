// Copyright Alexander Meuer

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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

void UTankAimingComponent::Initialize(UTankBarrel* barrel, UTankTurret* turret, UParticleSystemComponent* muzzleFlash)
{
	Barrel = barrel;
	Turret = turret;
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

void UTankAimingComponent::PointBarrelAt(FVector const & aimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	const auto barrelRotator = Barrel->GetForwardVector().ToOrientationRotator();
	const auto aimRotator = aimDirection.ToOrientationRotator();
	const auto deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate( deltaRotator.Pitch );
	Turret->Rotate ( deltaRotator.Yaw   );
}