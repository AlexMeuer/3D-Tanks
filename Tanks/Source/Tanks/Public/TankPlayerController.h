// Copyright Alexander Meuer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

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
