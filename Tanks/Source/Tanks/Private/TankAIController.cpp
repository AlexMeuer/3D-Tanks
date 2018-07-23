// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardPlayerTank();
}

void ATankAIController::AimTowardPlayerTank()
{
	ATank* const controlledTank = Cast<ATank>(GetPawn());
	if (controlledTank)
	{
		const ATank* const playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (playerTank)
		{
			controlledTank->AimAt(playerTank->GetActorLocation());
			controlledTank->Fire();
		}
	}
}

