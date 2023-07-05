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
	Type = InventoryType::Equip;
}

TArray<class AItem*> UInventory::GetInventory()
{
	if (Type == Equip) return EquipItems;
	else if (Type == Use) return UseItems;
	else return EtcItems;
	
}

void UInventory::GainNewWeapon(AWeapon* Item)
{
	
	if(Item->GetType() == WEAPON_SWORD)
		UE_LOG(LogTemp, Warning, TEXT("Sword Gain!"));
	if (Item->GetType() == WEAPON_ARROW)
		UE_LOG(LogTemp, Warning, TEXT("Bow Gain!"));

	int Index = FindEmptySlotIndex(EquipItems);

	if (Index == -1)
		return;//ºóÄ­ ¾øÀ½
	Item->SetItemMesh();
	EquipItems[Index] = Item;
}

void UInventory::GainNewUseItem(AUseItem* Item)
{
	UE_LOG(LogTemp, Warning, TEXT("UseItem Gain!"));
}

int UInventory::FindEmptySlotIndex(TArray<class AItem*>& ItemArray)
{
	for (int i = 0; i < MAX_Inventory; i++)
	{
		if (ItemArray[i] == nullptr) return i;
	}

	return -1;
}

void UInventory::GainNewItem(AItem* Item)
{
	Item->SetInventory(this);
	auto Weapon = Cast<AWeapon>(Item);
	if (Weapon != nullptr) GainNewWeapon(Weapon);
	
	auto UseItem = Cast<AUseItem>(Item);
	if (UseItem != nullptr) GainNewUseItem(UseItem);
}

void UInventory::RemoveWeapon(int SlotIndex)
{
	EquipItems[SlotIndex] = nullptr;
}




