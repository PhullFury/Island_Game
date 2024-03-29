// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandMan.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Island_Game/Actor/EquippableActor.h"
#include "Island_Game/Actor/SpawnableActor.h"
#include "Island_Game/Components/InventoryComponent.h"
#include "Island_Game/Objects/Items.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#define OUT

// Sets default values
AIslandMan::AIslandMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.f, 60.f);

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->bUsePawnControlRotation = true;

	WeaponSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Spawn Point"));
	WeaponSpawnPoint->SetupAttachment(FPCamera);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Invetory"));
	Inventory->Capacity = 20;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle"));
}

// Called when the game starts or when spawned
void AIslandMan::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = IslandManSpeed;
	CurrentSprintModifier = 1;
	bIsSprinting = false;
	CurrentHoldPower = 0.1;
	bIsHolding = false;
}

// Called every frame
void AIslandMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);
	SetHold(DeltaTime);

	GetController()->GetPlayerViewPoint(OUT IslandManLocation, OUT IslandManRotation);
	TargetLocation = IslandManLocation + IslandManRotation.Vector() * Reach;
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(TargetLocation);
	}
	if (bShowDebug) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Red, FString::Printf(TEXT("Current Hold Rate: %f"), CurrentHoldPower));
		//GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Red, FString::Printf(TEXT("Current Speed Modifier: %f"), CurrentSprintModifier));
		//DrawDebugLine(GetWorld(), IslandManLocation, IslandManLocation + IslandManRotation.Vector() * Reach, FColor::Red);
	}
}

// Called to bind functionality to input
void AIslandMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AIslandMan::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Sideways"), this, &AIslandMan::MoveSideways);
	PlayerInputComponent->BindAxis(TEXT("LookVertical"), this, &AIslandMan::LookVertical);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &AIslandMan::LookHorizontal);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AIslandMan::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AIslandMan::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &AIslandMan::Grab);
	PlayerInputComponent->BindAction(TEXT("Grab"), IE_Released, this, &AIslandMan::Release);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AIslandMan::Interact);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AIslandMan::StartAttack);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Released, this, &AIslandMan::StopAttack);
}

void AIslandMan::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AIslandMan::MoveSideways(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AIslandMan::LookVertical(float AxisValue)
{
	AddControllerPitchInput(AxisValue * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AIslandMan::LookHorizontal(float AxisValue)
{
	AddControllerYawInput(AxisValue * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AIslandMan::StartSprint()
{
	bIsSprinting = true;
}

void AIslandMan::StopSprint()
{
	bIsSprinting = false;
}

void AIslandMan::SetSpeed(float DeltaTime)
{
	GetCharacterMovement()->MaxWalkSpeed = IslandManSpeed * CurrentSprintModifier;
	if (GetVelocity().Z == 0)
	{
		if (bIsSprinting)
		{
			CurrentSprintModifier = FMath::FInterpTo(CurrentSprintModifier, MaxSprintModifier, DeltaTime, SprintRate);
			if (CurrentSprintModifier >= MaxSprintModifier - 0.2)
			{
				CurrentSprintModifier = MaxSprintModifier;
			}
			if (GetVelocity().IsZero())
			{
				CurrentSprintModifier = 1;
			}
		}
		else if (!bIsSprinting)
		{
			CurrentSprintModifier = FMath::FInterpTo(CurrentSprintModifier, 1, DeltaTime, SprintRate);
			if (CurrentSprintModifier <= 1.2 || GetVelocity().IsZero())
			{
				CurrentSprintModifier = 1;
			}
		}
	}
}

void AIslandMan::Interact()
{
	if (GetHitResults().GetActor()) 
	{
		ASpawnableActor* SpawnedActor = Cast<ASpawnableActor>(GetHitResults().GetActor());
		Inventory->AddItem(SpawnedActor->SpawnInventory->Items[0]);
		SpawnedActor->Destroy();
	}	
}

void AIslandMan::StartAttack()
{
	bIsHolding = true;
	if (Equippable != nullptr)
	{
		if (!Equippable->bIsHoldable)
		{
			Equippable->Attack(CurrentHoldPower);
		}
	}
}

void AIslandMan::StopAttack()
{
	bIsHolding = false;
	if (Equippable != nullptr)
	{
		if (Equippable->bIsHoldable)
		{
			Equippable->Attack(CurrentHoldPower);
		}
	}
}

void AIslandMan::SetHold(float DeltaTime)
{
	if (bIsHolding)
	{
		CurrentHoldPower = FMath::FInterpTo(CurrentHoldPower, MaxHoldPower, DeltaTime, HoldRate);
		if (CurrentHoldPower >= MaxHoldPower - 0.1)
		{
			CurrentHoldPower = MaxHoldPower;
		}
	}
	else
	{
		CurrentHoldPower = 0.1;
	}
}

void AIslandMan::UseItem(UItems* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); //bp version
	}
}

void AIslandMan::Grab()
{
	if (GetHitResults().GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(GetHitResults().GetComponent(), NAME_None, TargetLocation);
	}
}

void AIslandMan::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult AIslandMan::GetHitResults()
{
	FHitResult Hits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByObjectType(Hits, IslandManLocation, TargetLocation, FCollisionObjectQueryParams(ECC_GameTraceChannel2/*Custom object type - Spawnables*/), Params);

	return Hits;
}

void AIslandMan::SetEquippable(class AEquippableActor* EquippableReference)
{
	Equippable = EquippableReference;
}