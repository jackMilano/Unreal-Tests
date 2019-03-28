// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AThirdPawn::AThirdPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Shapes/Sphere.Sphere"));

	// Create mesh component for the sphere
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere0"));
	Sphere->SetStaticMesh(BallMesh.Object);
	Sphere->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Sphere->SetSimulatePhysics(true);
	Sphere->SetAngularDamping(0.1f);
	Sphere->SetLinearDamping(0.1f);
	Sphere->BodyInstance.MassScale = 3.5f;
	Sphere->BodyInstance.MaxAngularVelocity = 800.0f;
	Sphere->SetNotifyRigidBodyCollision(true);
	RootComponent = Sphere;

	// Create a camera boom attached to the root (sphere)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bAbsoluteRotation = true; // Rotation of the sphere should not affect rotation of boom
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Set up forces
	RollTorque = 50000000.0f;
}

// Called when the game starts or when spawned
void AThirdPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AThirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::D, 1.f));
	}

	InputComponent->BindAxis("MoveForward", this, &AThirdPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AThirdPawn::MoveRight);
}

void AThirdPawn::MoveForward(float AxisValue)
{
	const FVector Torque = FVector(0.0f, AxisValue * RollTorque, 0.0f);
	Sphere->AddTorqueInRadians(Torque);
}

void AThirdPawn::MoveRight(float AxisValue)
{
	const FVector Torque = FVector(AxisValue * RollTorque * -1.0f, 0.0f, 0.0f);
	Sphere->AddTorqueInRadians(Torque);
}

