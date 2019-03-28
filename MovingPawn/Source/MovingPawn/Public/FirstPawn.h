// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FirstPawn.generated.h"

// We move this pawn using `SetActorLocation`.

UCLASS()
class MOVINGPAWN_API AFirstPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFirstPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		float Speed = 200.0f;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	void MoveForward(float Val);
	void MoveRight(float Val);
	void MoveUp(float Val);

	AActor* Owner;
	APlayerController* PlayerController;
	FVector CurrentVelocity;
	UWorld* World;
};
