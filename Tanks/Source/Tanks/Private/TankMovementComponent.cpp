// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* left, UTankTrack* right)
{
	if (!left || !right) { return; }

	LeftTrack = left;
	RightTrack = right;
}

void UTankMovementComponent::IntendMoveForward(float axisThrow)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(axisThrow);
	RightTrack->SetThrottle(axisThrow);

	// TODO: Prevent double speed due to dual control use.
}

void UTankMovementComponent::IntendTurnRight(float axisThrow)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(axisThrow);
	RightTrack->SetThrottle(-axisThrow);

	// TODO: Prevent double speed due to dual control use.
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	const auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const auto forwardIntention = MoveVelocity.GetSafeNormal();
	
	const auto forwardThrow = FVector::DotProduct(tankForward, forwardIntention);

	IntendMoveForward(forwardThrow);
}
