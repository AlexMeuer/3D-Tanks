// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController (%s) not possessing a Tank!"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController (%s) possessing Tank (%s)"), *GetName(), *controlledTank->GetName());
	}
}
