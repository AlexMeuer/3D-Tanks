// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class UParticleSystemComponent;

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* barrel, UTankTurret* turret, UParticleSystemComponent* muzzleFlash);

	void AimAt(FVector const & location);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UParticleSystemComponent* MuzzleFlash = nullptr;

	UTankAimingComponent();

	void PointBarrelAt(FVector const & aimDirection);
};
