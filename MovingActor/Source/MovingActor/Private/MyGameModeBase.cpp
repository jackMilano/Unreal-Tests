// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "Public/MyDefaultPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyDefaultPawn::StaticClass();
}