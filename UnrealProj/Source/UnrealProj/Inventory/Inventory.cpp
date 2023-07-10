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

TArray<class AItem*>& UInventory::GetInventory()
{
	if (Type == Equip) return EquipItems;
	else if (Type == Use) return UseItems;
	else return EtcItems;
	
}

void UInventory::GainNewWeapon(AWeapon* Item, int SlotIndex)
{
	
	if(Item->GetType() == WEAPON_SWORD)
		UE_LOG(LogTemp, Warning, TEXT("Sword Gain!"));
	if (Item->GetType() == WEAPON_ARROW)
		UE_LOG(LogTemp, Warning, TEXT("Bow Gain!"));

	int Index;
	if (SlotIndex == -1)
		Index = FindEmptySlotIndex(EquipItems);
	else
		Index = SlotIndex;

	if (Index == -1)
		return;//ºóÄ­ ¾øÀ½
	Item->SetItemMesh();
	Item->SetSlotIndex(Index);
	EquipItems[Index] = Item;
	
}

void UInventory::GainNewUseItem(AUseItem* Item, int SlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UseItem Gain!"));
	int Index;
	int HavingIndex;

	HavingIndex = FindItem(UseItems, Item->GetId());
	if (HavingIndex != -1)
	{
		UseItems[HavingIndex]->SetCount(UseItems[HavingIndex]->GetCount() + 1);
		return;
	}

	if (SlotIndex == -1)
		Index = FindEmptySlotIndex(UseItems);
	else
		Index = SlotIndex;

	if (Index == -1)
		return;//ºóÄ­ ¾øÀ½
	Item->SetSlotIndex(Index);
	UseItems[Index] = Item;
}

int UInventory::FindEmptySlotIndex(TArray<class AItem*>& ItemArray)
{
	for (int i = 0; i < MAX_Inventory; i++)
	{
		if (ItemArray[i] == nullptr) return i;
	}

	return -1;
}

int UInventory::FindItem(TArray<AItem*>& ItemArray, int Id)
{
	for (int i = 0; i < MAX_Inventory; i++)
	{
		if (ItemArray[i] == nullptr) continue;
		if (ItemArray[i]->GetId() == Id && ItemArray[i]->GetCount() < 10)
			return i;
	}
	return -1;
}

void UInventory::GainNewItem(AItem* Item, int SlotIndex)
{
	Item->SetInventory(this);
	auto Weapon = Cast<AWeapon>(Item);
	if (Weapon != nullptr) GainNewWeapon(Weapon, SlotIndex);
	
	auto UseItem = Cast<AUseItem>(Item);
	if (UseItem != nullptr) GainNewUseItem(UseItem, SlotIndex);
}

void UInventory::EmptySlot(TArray<class AItem*>& ItemArray, int Index)
{
	ItemArray[Index] = nullptr;
}

void UInventory::SwapItem(int DragedIndex, int ArrivedIndex)
{
	AItem* ItemTemp = GetInventory()[ArrivedIndex];
	GetInventory()[ArrivedIndex] = GetInventory()[DragedIndex];
	GetInventory()[DragedIndex] = ItemTemp;

	if(GetInventory()[ArrivedIndex] != nullptr)
		GetInventory()[ArrivedIndex]->SetSlotIndex(ArrivedIndex);

	if (GetInventory()[DragedIndex] != nullptr)
		GetInventory()[DragedIndex]->SetSlotIndex(DragedIndex);
	
}




