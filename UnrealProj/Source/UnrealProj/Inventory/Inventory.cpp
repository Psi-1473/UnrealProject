// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	//EquipItems.Init(ITEM_NONE, MAX_Inventory);
	//UseItems.Init(ITEM_NONE, MAX_Inventory);
	//EtcItems.Init(ITEM_NONE, MAX_Inventory);
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	
}

void UInventory::GainItem()
{
}


