// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippableActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
AEquippableActor::AEquippableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AEquippableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquippableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquippableActor::Attack(float Modifier)
{
	if (bIsHoldable)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, FString::Printf(TEXT("HOLD Attack!!")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, FString::Printf(TEXT("Attack!!")));
	}	
}