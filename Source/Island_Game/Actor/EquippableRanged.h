// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquippableActor.h"
#include "EquippableRanged.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_GAME_API AEquippableRanged : public AEquippableActor
{
	GENERATED_BODY()
	
public:
	AEquippableRanged();

protected:
	virtual void Attack(float Modifier) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		float ProjectileSpeed = 300.f;
};