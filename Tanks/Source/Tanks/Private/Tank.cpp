// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::Fire()
{
	if (IsReloaded())
	{
/*
		const FName socketName("Projectile");

		const auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(socketName),
			Barrel->GetSocketRotation(socketName)
			);

		projectile->Launch(LaunchSpeed);
*/
		LastFireTime = GetWorld()->GetTimeSeconds();

		//if (MuzzleFlash)
		//{
		//	MuzzleFlash->ActivateSystem();
		//}
	}
}

bool ATank::IsReloaded() const
{
	return (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
}
