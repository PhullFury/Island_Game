// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"

void UHealthItem::Use(class AIslandMan* Character)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString::Printf(TEXT("The Player was healed")));
}