// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDefaultPawn.h"
#include "Engine/World.h"
#include "Public/TestActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AMyDefaultPawn::AMyDefaultPawn()
{
}

// Called when the game starts or when spawned
void AMyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();

	// Make a location for the new actor to spawn at
	FVector NewLocation = FVector(0.0f, 0.0f, GetActorLocation().Z + 2.0f);

	// Spawn the new actor
	ATestActor* NewActor = GetWorld()->SpawnActor<ATestActor>(NewLocation, FRotator::ZeroRotator);
}

// Called every frame
void AMyDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}