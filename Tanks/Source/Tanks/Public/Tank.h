// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector const & location);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// The barrel to move about when aiming.
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMeshComponents(UTankBarrel* barrel, UTankTurret* turret);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMuzzleFlash(UParticleSystem* muzzleFlash);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	UParticleSystem* MuzzleFlash = nullptr;

	// Use to spawn projectiles.
	UTankBarrel* Barrel = nullptr;

	float LastFireTime = 0.f;

private:
	bool IsReloaded() const;
};
