// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "../Items/Item.h"
#include "../Items/UseItem/UseItem.h"
#include "../Items/MiscItem/MiscItem.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Weapons/Sword.h"
#include "../Items/Weapons/Bow.h"
#include "../Widgets/Popup/Widget_Inventory.h"
#include "../Managers/UIManager.h"
#include "../MyGameInstance.h"
#include "../DEFINE.h"
#include "../Creatures/Player/MyPlayer.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	EquipItems.Init(nullptr, MAX_Inventory);
	UseItems.Init(nullptr, MAX_Inventory);
	MiscItems.Init(nullptr, MAX_Inventory);
	Type = Equip;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();
	Type = InventoryType::Equip;
	Gold = 5000;
}

TArray<class AItem*>& UInventory::GetInventory()
{
	if (Type == Equip) return EquipItems;
	else if (Type == Use) return UseItems;
	else return MiscItems;
	
}

void UInventory::GainNewItem(ItemType IType, int Id, int SlotIndex)
{
	AItem* NewItem = nullptr;
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	if (IType == ItemType::ITEM_USE)
	{
		NewItem = CreateUseItem(Id);
		GainNewUseItem(NewItem, SlotIndex);
		GInstance->CheckQuest(QUEST_ITEM, Id, OwnerPlayer, (int)QITEM_USE);
	}
	else if (IType == ItemType::ITEM_MISC)
	{
		NewItem = CreateMiscItem(Id);
		GainNewMiscItem(NewItem, SlotIndex);
		//GInstance->CheckQuest(QUEST_ITEM, Id, OwnerPlayer, (int)QITEM_USE);
	}
	else //무기
	{
		if (IType == ItemType::ITEM_SWORD)
			NewItem = CreateWeapon(Id, WEAPONTYPE::WEAPON_SWORD);
		else if (IType == ItemType::ITEM_BOW)
			NewItem = CreateWeapon(Id, WEAPONTYPE::WEAPON_BOW);

		GainNewWeapon(NewItem, SlotIndex);
		GInstance->CheckQuest(QUEST_ITEM, Id, OwnerPlayer, (int)QITEM_EQUIP);
	}
	
	NewItem->SetInventory(this);
	NewItem->SetCount(1);
	NewItem->SetOwner(Cast<AActor>(OwnerPlayer));
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

	if (GetInventory()[ArrivedIndex] != nullptr)
		GetInventory()[ArrivedIndex]->SetSlotIndex(ArrivedIndex);

	if (GetInventory()[DragedIndex] != nullptr)
		GetInventory()[DragedIndex]->SetSlotIndex(DragedIndex);

}

void UInventory::AddGold(int Value)
{
	Gold += Value;

	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	auto Widget = Cast<UWidget_Inventory>(GInstance->GetUIMgr()->GetUI(UIType::Inventory));
	if (Widget != nullptr)
		Widget->RefreshGoldText(OwnerPlayer);
}
void UInventory::UseGold(int Value)
{
	Gold -= Value;

	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	auto Widget = Cast<UWidget_Inventory>(GInstance->GetUIMgr()->GetUI(UIType::Inventory));
	if (Widget != nullptr)
		Widget->RefreshGoldText(OwnerPlayer);
}

void UInventory::GainNewWeapon(AItem* Item, int SlotIndex)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	auto Weapon = Cast<AWeapon>(Item);
	if (Weapon == nullptr) return;

	int Index;
	if (SlotIndex == SLOTINDEX_NOT_SPECIFIED)
		Index = FindEmptySlotIndex(EquipItems);
	else
		Index = SlotIndex;

	if (Index == FIND_FAILED)
		return;

	Item->SetItemMesh(GInstance);
	Item->SetSlotIndex(Index);
	EquipItems[Index] = Item;
	
}
void UInventory::GainNewUseItem(AItem* Item, int SlotIndex)
{
	auto UseItem = Cast<AUseItem>(Item);
	if (UseItem == nullptr) return;

	int Index;
	int HavingIndex;

	HavingIndex = FindItem(UseItems, Item->GetId());
	if (HavingIndex != FIND_FAILED)
	{
		UseItems[HavingIndex]->SetCount(UseItems[HavingIndex]->GetCount() + 1);
		return;
	}

	if (SlotIndex == SLOTINDEX_NOT_SPECIFIED)
		Index = FindEmptySlotIndex(UseItems);
	else
		Index = SlotIndex;

	if (Index == FIND_FAILED)
		return;
	Item->SetSlotIndex(Index);
	UseItems[Index] = Item;
}

void UInventory::GainNewMiscItem(AItem* Item, int SlotIndex)
{
	auto MiscItem = Cast<AMiscItem>(Item);
	if (MiscItem == nullptr) return;

	int Index;
	int HavingIndex;

	HavingIndex = FindItem(MiscItems, Item->GetId());
	if (HavingIndex != FIND_FAILED)
	{
		MiscItems[HavingIndex]->SetCount(MiscItems[HavingIndex]->GetCount() + 1);
		return;
	}

	if (SlotIndex == SLOTINDEX_NOT_SPECIFIED)
		Index = FindEmptySlotIndex(MiscItems);
	else
		Index = SlotIndex;

	if (Index == FIND_FAILED)
		return;
	Item->SetSlotIndex(Index);
	MiscItems[Index] = Item;
}

AWeapon* UInventory::CreateWeapon(int Id, WEAPONTYPE WType)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance()); // 나중에 Weapon Data 끌고오기 위함
	AWeapon* Weapon = nullptr;

	if(WType == WEAPONTYPE::WEAPON_SWORD)
		Weapon = NewObject<ASword>();
	else if(WType == WEAPONTYPE::WEAPON_BOW)
		Weapon = NewObject<ABow>();

	Weapon->SetId(Id);
	Weapon->SetWeaponType(WType);
	Weapon->LoadItemData(GInstance);
	return Weapon;
}

AUseItem* UInventory::CreateUseItem(int Id)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	AUseItem* UseItem = NewObject<AUseItem>();

	UseItem->SetId(Id);
	UseItem->LoadItemData(GInstance);
	return UseItem;
}

AMiscItem* UInventory::CreateMiscItem(int Id)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	AMiscItem* MiscItem = NewObject<AMiscItem>();

	MiscItem->SetId(Id);
	MiscItem->LoadItemData(GInstance);
	return MiscItem;
}

int UInventory::FindEmptySlotIndex(TArray<class AItem*>& ItemArray)
{
	for (int i = 0; i < MAX_Inventory; i++)
		if (ItemArray[i] == nullptr) return i;

	return FIND_FAILED;
}
int UInventory::FindItem(TArray<AItem*>& ItemArray, int Id)
{
	for (int i = 0; i < MAX_Inventory; i++)
	{
		if (ItemArray[i] == nullptr) continue;
		if (ItemArray[i]->GetId() == Id && ItemArray[i]->GetCount() < 10)
			return i;
	}
	return FIND_FAILED;
}





