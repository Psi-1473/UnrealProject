// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	EquipItems.Init(nullptr, MAX_Inventory);
	UseItems.Init(nullptr, MAX_Inventory);
	EtcItems.Init(nullptr, MAX_Inventory);
	Type = Equip;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();
}

TArray<class AItem*> UInventory::GetInventory()
{
	if (Type == Equip) return EquipItems;
	else if (Type == Use) return UseItems;
	else return EtcItems;
	
}

void UInventory::GainItem()
{
}


