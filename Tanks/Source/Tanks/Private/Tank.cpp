// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"

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

void ATank::SetMeshComponents(UTankBarrel * barrel, UTankTurret* turret)
{
	AimingComponent->SetMeshComponents(barrel, turret);
}
