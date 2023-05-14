// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandMan.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AIslandMan::AIslandMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.f, 60.f);

	/*FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	FPCamera->bUsePawnControlRotation = true;*/
}

// Called when the game starts or when spawned
void AIslandMan::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = IslandManSpeed;
	CurrentSprintModifier = 1;
	bIsSprinting = false;
}

// Called every frame
void AIslandMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);
	if (bShowDebug) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Red, FString::Printf(TEXT("Current Speed Modifier: %f"), CurrentSprintModifier));
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
		if (bIsSprinting && !GetVelocity().IsZero())
		{
			CurrentSprintModifier = FMath::FInterpTo(CurrentSprintModifier, MaxSprintModifier, DeltaTime, SprintRate);
			if (CurrentSprintModifier >= MaxSprintModifier - 0.2)
			{
				CurrentSprintModifier = MaxSprintModifier;
			}
		}
		else if (!bIsSprinting)
		{
			CurrentSprintModifier = FMath::FInterpTo(CurrentSprintModifier, 1, DeltaTime, SprintRate);
			if (CurrentSprintModifier <= 1.2 || GetVelocity().IsZero())
			{
				CurrentSprintModifier = 1;
			}
			/*if (GetVelocity().IsZero())
			{
				CurrentSprintModifier = 1;
			}*/
		}
	}
}