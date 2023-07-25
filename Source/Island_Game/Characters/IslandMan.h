// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IslandMan.generated.h"

UCLASS()
class ISLAND_GAME_API AIslandMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIslandMan();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UItems* Item);

	FVector IslandManLocation;
	FRotator IslandManRotation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Items", meta = (AllowPrivateAccess = "true"))
		float Reach = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* WeaponSpawnPoint;

	void SetEquippable(class AEquippableActor* EquippableReference);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FPCamera;
	UPROPERTY(EditAnywhere, Category = "Physics")
		class UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float TurnRate = 50.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float IslandManSpeed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MaxSprintModifier = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float SprintRate = 2.f;
	UPROPERTY(EditAnywhere, Category = "General", meta = (AllowPrivateAccess = "true"))
		bool bShowDebug = false;
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		float MaxHoldPower = 1.f;
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		float HoldRate = 2.f;

	float CurrentSprintModifier;
	bool bIsSprinting;
	float CurrentHoldPower;
	bool bIsHolding;
	AEquippableActor* Equippable;

	void MoveForward(float AxisValue);
	void MoveSideways(float AxisValue);
	void LookVertical(float AxisValue);
	void LookHorizontal(float AxisValue);
	void StartSprint();
	void StopSprint();
	void SetSpeed(float DeltaTime);
	void Grab();
	void Release();
	FHitResult GetHitResults();
	void Interact();
	void StartAttack();
	void StopAttack();
	void SetHold(float DeltaTime);
};