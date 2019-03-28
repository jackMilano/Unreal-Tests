// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SecondPawnMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class MOVINGPAWN_API USecondPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	const float MAX_SPEED = 150.0f; // Unreal Units per second
};
