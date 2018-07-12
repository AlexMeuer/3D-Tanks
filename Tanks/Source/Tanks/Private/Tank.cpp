// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

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
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't fire: No barrel set!"));
		return;
	}

	const FName socketName("Projectile");

	const auto projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(socketName),
		Barrel->GetSocketRotation(socketName)
	);

	projectile->Launch(LaunchSpeed);
}

void ATank::SetMeshComponents(UTankBarrel* barrel, UTankTurret* turret)
{
	AimingComponent->SetMeshComponents(barrel, turret);
	Barrel = barrel;
}
