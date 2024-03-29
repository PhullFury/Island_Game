// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableActor.h"
#include "Engine/StaticMesh.h"
#include "Island_Game/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnableActor::ASpawnableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	SpawnInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Invetory"));
	SpawnInventory->Capacity = 1;
}

// Called when the game starts or when spawned
void ASpawnableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}