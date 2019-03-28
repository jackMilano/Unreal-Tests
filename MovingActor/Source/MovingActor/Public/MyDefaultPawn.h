// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MyDefaultPawn.generated.h"

/**
 *
 */
UCLASS()
class MOVINGACTOR_API AMyDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyDefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
