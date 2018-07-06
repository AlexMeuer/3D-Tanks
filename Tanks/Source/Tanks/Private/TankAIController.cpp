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

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* controlledTank = GetControlledTank();
	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController (%s) possessing Tank (%s)"), *GetName(), *controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController (%s) not possessing a Tank!"), *GetName());
	}

	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Found player tank: %s"), *GetName(), *playerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to find player Tank!"), *GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerCtrler = GetWorld()->GetFirstPlayerController();
	auto tankCtrler = Cast<ATankPlayerController>(playerCtrler);

	return tankCtrler
		? tankCtrler->GetControlledTank()
		: nullptr;
}

void ATankAIController::AimTowardPlayerTank()
{
	ATank* controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not controlling a Tank!"), *GetName());
		return;
	}

	ATank* playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to find player Tank!"), *GetName());
		return;
	}

	controlledTank->AimAt(playerTank->GetActorLocation());
}

