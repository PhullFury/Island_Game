// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

UCLASS()
class ISLAND_GAME_API ASpawnableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnableActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* SpawnInventory;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:	
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	class AIslandMan* Player;
};