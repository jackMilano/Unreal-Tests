// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SecondPawn.generated.h"

// Moving a pawn using `MovementComponent`, like in the `DefaultPawn`.
// SOURCE: https://docs.unrealengine.com/en-US/Gameplay/Framework/Pawn

// Using Components to separate functionality is a good practice to reduce clutter as your project grows and your Pawns become more complex.
// SOURCE: https://docs.unrealengine.com/en-us/Programming/Tutorials/Components
UCLASS()
class MOVINGPAWN_API ASecondPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASecondPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);

	class USecondPawnMovementComponent* OurMovementComponent;
};
