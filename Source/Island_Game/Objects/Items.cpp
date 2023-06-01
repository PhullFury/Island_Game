// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"

UItems::UItems()
{
	Weight = 0;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UItems::Use(AIslandMan* Character)
{

}