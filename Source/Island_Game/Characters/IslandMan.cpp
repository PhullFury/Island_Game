// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/IslandMan.h"

// Sets default values
AIslandMan::AIslandMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIslandMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIslandMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIslandMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

