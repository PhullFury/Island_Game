// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class ISLAND_GAME_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Test;
	void SetSpeed(float NewSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"));
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float LifeSpan = 60.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float GravityScale = 0.f;
};
