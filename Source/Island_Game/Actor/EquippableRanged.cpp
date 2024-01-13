// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippableRanged.h"
#include "Island_Game/Actor/ProjectileBase.h"

AEquippableRanged::AEquippableRanged()
{
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(Root);
}

void AEquippableRanged::Attack(float Modifier)
{
	if (bIsHoldable) 
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
		Projectile->SetOwner(this);
		/*Projectile->Speed = 300.f;
		Projectile->Test = 1;*/
		Projectile->SetSpeed(ProjectileSpeed);
		//GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, FString::Printf(TEXT("Throw projectile")));
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, FString::Printf(TEXT("BASE Projectile Speed: %f"), ProjectileSpeed));
	}	
}