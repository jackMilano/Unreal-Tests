// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPawnGameModeBase.h"
#include "Public/FirstPawn.h"
#include "Public/SecondPawn.h"
#include "Public/ThirdPawn.h"
#include "Public/FourthPawn.h"
#include "Public/MyCustomPlayerController.h"

AMovingPawnGameModeBase::AMovingPawnGameModeBase()
{
    DefaultPawnClass = AFirstPawn::StaticClass();
    //DefaultPawnClass = ASecondPawn::StaticClass();
    //DefaultPawnClass = AThirdPawn::StaticClass();
    //DefaultPawnClass = AFourthPawn::StaticClass();

    //PlayerControllerClass = AMyCustomPlayerController::StaticClass();
}
