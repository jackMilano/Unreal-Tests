// Fill out your copyright notice in the Description page of Project Settings.

#include "SecondPawnMovementComponent.h"

void USecondPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get (and then clear) the movement vector that we set in ASecondPawn::Tick
	FVector ClampedInput = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	FVector DesiredMovementThisFrame = ClampedInput * DeltaTime * MAX_SPEED;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		// `SafeMoveUpdatedComponent` uses Unreal Engine physics to move our Pawn Movement Component while respecting
		// solid barriers.
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			// `SlideAlongSurface` handles the calculations and physics involved with sliding smoothly along collision
			// surfaces like walls and ramps when a move results in a collision, rather than simply stopping in place
			// and sticking to the wall or ramp.
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}
