// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Island_Game/Objects/Items.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (UItems* Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UInventoryComponent::AddItem(UItems* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwnerInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);
	OnIventoryUpdated.Broadcast(); //updates the UIs

	return true;
}

bool UInventoryComponent::RemoveItem(UItems* Item)
{
	if (Item)
	{
		Item->OwnerInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnIventoryUpdated.Broadcast();
		return true;
	}
	return false;
}
