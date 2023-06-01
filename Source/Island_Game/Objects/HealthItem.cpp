// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"
#include "Island_Game/Components/InventoryComponent.h"

void UHealthItem::Use(class AIslandMan* Character)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::Printf(TEXT("The Player was healed")));

	if (OwnerInventory)
	{
		OwnerInventory->RemoveItem(this);
	}
}