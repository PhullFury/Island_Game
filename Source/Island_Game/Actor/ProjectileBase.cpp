// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(Root);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->InitialSpeed = 300.f;
	ProjectileMovement->MaxSpeed = 300.f;
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(2, 2, FColor::Red, FString::Printf(TEXT("Current Speed: %f"), ProjectileMovement->GetMaxSpeed()));
	GEngine->AddOnScreenDebugMessage(3, 2, FColor::Red, FString::Printf(TEXT("Projectile Speed: %f"), Speed));
	GEngine->AddOnScreenDebugMessage(4, 2, FColor::Red, FString::Printf(TEXT("Test: %f"), Test));
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::SetSpeed(float NewSpeed)
{
	Speed = NewSpeed;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
}