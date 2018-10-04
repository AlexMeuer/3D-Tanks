// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	AimTowardPlayerTank();
}

void ATankAIController::AimTowardPlayerTank()
{
	auto controlledTank = GetPawn();
	if (ensure(controlledTank))
	{
		APawn* const playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (ensure(playerTank))
		{
			MoveToActor(playerTank, AcceptanceRadius);

			auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
			if (ensure(aimingComponent))
			{
				aimingComponent->AimAt(playerTank->GetActorLocation());
			}

			aimingComponent->Fire();
		}
	}
}

