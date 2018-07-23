// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank() :
	AimingComponent(CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector const & location)
{
	AimingComponent->AimAt(location, LaunchSpeed);
}

void ATank::Fire()
{
	if (Barrel && IsReloaded())
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
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				MuzzleFlash,
				FTransform(
					Barrel->GetSocketRotation(socketName),
					Barrel->GetSocketLocation(socketName),
					FVector::OneVector
				),
				true
			);
		}
	}
}

void ATank::SetMeshComponents(UTankBarrel* barrel, UTankTurret* turret)
{
	AimingComponent->SetMeshComponents(barrel, turret);
	Barrel = barrel;
}

void ATank::SetMuzzleFlash(UParticleSystem * muzzleFlash)
{
	MuzzleFlash = muzzleFlash;
}

bool ATank::IsReloaded() const
{
	return (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
}
