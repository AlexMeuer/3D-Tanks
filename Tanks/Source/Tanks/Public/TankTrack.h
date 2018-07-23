// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to set maximum driving forace and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);

private:
	// Max force in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 4000000.f; // Assuming 40 tonne tank at 1g acceleration
	
};
