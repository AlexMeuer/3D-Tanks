// Copyright Alexander Meuer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* left, UTankTrack* right);

	UFUNCTION(BlueprintCallable, Category = "FlyByWire")
	void IntendMoveForward(float axisThrow);

	UFUNCTION(BlueprintCallable, Category = "FlyByWire")
	void IntendTurnRight(float axisThrow);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	

	// Called from the pathfinding logic by the AI controllers.
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
