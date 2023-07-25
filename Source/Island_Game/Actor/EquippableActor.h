// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippableActor.generated.h"

UCLASS()
class ISLAND_GAME_API AEquippableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquippableActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		bool bIsHoldable = false;

	void Attack(float Modifier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* SkeletalMesh;
};