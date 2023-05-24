// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_GAME_API UHealthItem : public UItems
{
	GENERATED_BODY()
	
protected:
	virtual void Use(class AIslandMan* Character) override;
};