// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.f, 1.f);
	
	const auto rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	const auto rotation = RelativeRotation.Yaw + rotationChange;
	
	SetRelativeRotation(FRotator(0, rotation, 0));
}
