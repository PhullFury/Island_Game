// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipItem.h"
#include "Island_Game/Actor/EquippableActor.h"
#include "Island_Game/Characters/IslandMan.h"
#include "Kismet/GameplayStatics.h"

void UEquipItem::Use(class AIslandMan* Character)
{
	AIslandMan* Player = Cast<AIslandMan>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!bIsEquipped)
	{
		FTransform SpawnTransform = Player->WeaponSpawnPoint->GetComponentTransform();
		EquippableActor = GetWorld()->SpawnActor<AEquippableActor>(EquippableActorClass, SpawnTransform);
		EquippableActor->AttachToComponent(Player->WeaponSpawnPoint, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		Player->SetEquippable(EquippableActor);
		bIsEquipped = true;
	}
	else if (bIsEquipped)
	{
		EquippableActor->Destroy();
		Player->SetEquippable(nullptr);
		bIsEquipped = false;
	}
}