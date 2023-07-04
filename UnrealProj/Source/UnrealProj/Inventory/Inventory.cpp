// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "../Items/Item.h"
#include "../Items/UseItem/UseItem.h"
#include "../Items/Weapons/Weapon.h"


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

void UInventory::GainNewWeapon(AWeapon* Item)
{
}

void UInventory::GainNewUseItem(AUseItem* Item)
{
}

void UInventory::ItemMake()
{
	Type = Use;
	UseItems[1] = NewObject<AUseItem>();
	UseItems[1]->SetId(1);
	UseItems[1]->SetCount(1);
	UseItems[1]->SetInventory(this);
}


