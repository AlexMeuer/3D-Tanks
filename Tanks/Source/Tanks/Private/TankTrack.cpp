// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle)
{
	const auto forceApplied = GetForwardVector() * throttle * MaxDrivingForce;

	const auto forceLocation = GetComponentLocation();

	const auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

