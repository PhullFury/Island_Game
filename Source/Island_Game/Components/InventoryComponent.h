// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//Blueprints bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ISLAND_GAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	bool AddItem(class UItems* Item);
	bool RemoveItem(class UItems* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UItems*> DefaultItems;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnIventoryUpdated OnIventoryUpdated;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
		TArray<class UItems*> Items;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:	
			
};