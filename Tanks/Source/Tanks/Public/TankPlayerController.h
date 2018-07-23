// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

private:

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f; // 10km default

	// Start the tank moving the barrel so that a shot would it where
	// the crosshair intersects the world.
	void AimTowardsCrosshair();

	// Returns true if hit landscape.
	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	bool GetLookDirection(FVector2D const & screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector const & lookDirection, FVector& outHitLocation) const;
};
