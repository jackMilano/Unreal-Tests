// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCustomPlayerController.h"

void AMyCustomPlayerController::InitInputSystem()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCustomPlayerController InitInputSystem."));

	Super::InitInputSystem();

	if (PlayerInput == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInput is null!"));
	}
}

void AMyCustomPlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCustomPlayerController SetupInputComponent."));

	Super::SetupInputComponent();

}

