// Fill out your copyright notice in the Description page of Project Settings.

#include "TestActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/CollisionProfile.h"

// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame. 
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a Box that reacts to physics
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBoxExtent(FVector(40.0f));
	BoxComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentHit.AddDynamic(this, &ATestActor::OnHit);

	// Create and position a mesh component so we can see where our sphere is
	UStaticMeshComponent* CubeVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	CubeVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		CubeVisual->SetStaticMesh(CubeVisualAsset.Object);
		CubeVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		CubeVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Create a particle system attached to the cube
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(CubeVisual);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Increment = FVector(0.0f, Speed, 0.0f) * DeltaTime;
	FVector NewLocation = GetActorLocation() + (Increment * Sign);

	SetActorLocation(NewLocation, true);
}

void ATestActor::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	FName CollisionProfileName = OtherComp->GetCollisionProfileName();
	if (CollisionProfileName == "InvisibleWall")
	{
		FString Name = OtherActor->GetName();
		Sign *= -1.0f;
	}
}
