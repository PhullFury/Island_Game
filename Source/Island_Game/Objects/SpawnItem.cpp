// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnItem.h"
#include "Island_Game/Actor/SpawnableActor.h"
#include "Island_Game/Characters/IslandMan.h"
#include "Island_Game/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void USpawnItem::Use(class AIslandMan* Character)
{
	if (OwnerInventory)
	{
		AIslandMan* Player = Cast<AIslandMan>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		FRotator SpawnRotation = FRotator(0, 0, 180) - Player->IslandManRotation;
		ASpawnableActor* SpawnActor = GetWorld()->SpawnActor<ASpawnableActor>(SpawnActorClass, Player->TargetLocation, SpawnRotation);
		OwnerInventory->RemoveItem(this);
	}
}