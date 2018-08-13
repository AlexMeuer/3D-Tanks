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
		APawn* const playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (playerTank)
		{
			MoveToActor(playerTank, AcceptanceRadius);

			controlledTank->AimAt(playerTank->GetActorLocation());

			controlledTank->Fire();
		}
	}
}

