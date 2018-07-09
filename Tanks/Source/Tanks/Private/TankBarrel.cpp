// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	const auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Elevating barrel -> %f"), time, relativeSpeed);
}


