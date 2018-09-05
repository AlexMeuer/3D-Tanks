// Copyright Alex Meuer

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent))
	{
		FoundAimingComponent(aimingComponent);
	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector hitLocation; // Out parameter
	if (GetSightRayHitLocation(hitLocation))
	{
		aimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	// Find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	const FVector2D screenLocation(
		viewportSizeX * CrossHairXLocation,
		viewportSizeY * CrossHairYLocation
	);

	// "De-project" the screen position of the crosshair to a world direction
	FVector lookDirection;
	return GetLookDirection(screenLocation, lookDirection) &&
		GetLookVectorHitLocation(lookDirection, outHitLocation); // Line-trace along that look direction, and see what we hit (up to max range)
}

bool ATankPlayerController::GetLookDirection(FVector2D const & screenLocation, FVector& outLookDirection) const
{
	FVector worldPosition; //Discarded
	return DeprojectScreenPositionToWorld(
		screenLocation.X,
		screenLocation.Y,
		worldPosition,
		outLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector const & lookDirection, FVector& outHitLocation) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		outHitLocation = hitResult.Location;
		return true;
	}
	return false;
}
