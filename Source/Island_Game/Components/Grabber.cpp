// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Island_Game/Characters/IslandMan.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentLocation = Player->IslandManLocation + Player->IslandManRotation.Vector() * Player->Reach;
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(CurrentLocation);
	}
}

void UGrabber::Grab()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::Printf(TEXT("Grab")));
	if (PhysicsHandle && GetHitResults().GetActor())
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, GetHitResults().GetActor()->GetActorNameOrLabel());
		UPrimitiveComponent* Comp = GetHitResults().GetComponent();
		PhysicsHandle->GrabComponentAtLocation(Comp, NAME_None, CurrentLocation);
	}
}

void UGrabber::Release()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::Printf(TEXT("Released")));
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetHitResults()
{
	FHitResult Hit;
	FVector Start = Player->IslandManLocation;
	FVector End = Player->IslandManRotation.Vector() * Player->Reach;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);
	
	GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, FCollisionObjectQueryParams(ECC_Pawn), Params);

	return Hit;
}