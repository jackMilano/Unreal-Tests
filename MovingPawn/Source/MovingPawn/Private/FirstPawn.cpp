// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
AFirstPawn::AFirstPawn()
{
    Owner = nullptr;
    PlayerController = nullptr;
    CurrentVelocity = FVector(0.0f);
    World = nullptr;

    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create a dummy root component we can attach things to.
    // NOTE: atleast a `UComponent` is required for the object move
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create a camera and a visible object
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

    // Attach our camera and visible object to our root component. Offset and rotate the camera.
    OurCamera->SetupAttachment(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-250.0f, -1.0f, 250.0f));
    OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFirstPawn::BeginPlay()
{
    Super::BeginPlay();

    Owner = GetOwner();
    World = GetWorld();

    PlayerController = World->GetFirstPlayerController();
}

// Called every frame
void AFirstPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle movement based on our "MoveForward" and "MoveRight" axes
    {
        if (!CurrentVelocity.IsZero())
        {
            FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
            SetActorLocation(NewLocation);
        }
    }
}

// Called to bind functionality to input
void AFirstPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);

    Super::SetupPlayerInputComponent(PlayerInputComponent);

    static bool bBindingsAdded = false;
    if (!bBindingsAdded)
    {
        bBindingsAdded = true;

        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::W, 1.f));
        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::S, -1.f));
        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::A, -1.f));
        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::D, 1.f));
        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveUp", EKeys::E, 1.f));
        UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveUp", EKeys::Q, -1.f));
    }

    PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPawn::MoveRight);
    PlayerInputComponent->BindAxis("MoveUp", this, &AFirstPawn::MoveUp);
}

void AFirstPawn::MoveForward(float Val)
{
    if (Val != 0.0f) {
        if (PlayerController)
        {
            // Move at Speed units per second forward or backward
            CurrentVelocity.X = FMath::Clamp(Val, -1.0f, 1.0f) * Speed;
        }
    }
    else
    {
        CurrentVelocity.X = 0.0f;
    }
}

void AFirstPawn::MoveRight(float Val)
{
    if (Val != 0.0f) {
        if (PlayerController)
        {
            // Move at Speed units per second right or left
            CurrentVelocity.Y = FMath::Clamp(Val, -1.0f, 1.0f) * Speed;
        }
    }
    else
    {
        CurrentVelocity.Y = 0.0f;
    }
}

void AFirstPawn::MoveUp(float Val)
{
    if (Val != 0.0f) {
        if (PlayerController)
        {
            // Move at Speed units per second up or down
            CurrentVelocity.Z = FMath::Clamp(Val, -1.0f, 1.0f) * Speed;
        }
    }
    else
    {
        CurrentVelocity.Z = 0.0f;
    }
}
