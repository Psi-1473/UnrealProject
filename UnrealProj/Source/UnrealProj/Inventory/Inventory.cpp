// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "../Items/Item.h"
#include "../Items/UseItem/UseItem.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Weapons/Sword.h"
#include "../Items/Weapons/Bow.h"
#include "../Widgets/Popup/Widget_Inventory.h"
#include "../Managers/UIManager.h"
#include "../MyGameInstance.h"
#include "../Creatures/Player/MyPlayer.h"


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
	Gold = 5000;
}

TArray<class AItem*>& UInventory::GetInventory()
{
	if (Type == Equip) return EquipItems;
	else if (Type == Use) return UseItems;
	else return EtcItems;
	
}

void UInventory::GainNewItem(ItemType IType, int Id, int SlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("GainNewItem"));
	AItem* NewItem;
	auto GInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	if (IType == ItemType::ITEM_USE)
	{
		NewItem = CreateUseItem(Id);
		GainNewUseItem(NewItem, SlotIndex);
		GInstance->CheckQuest(QUEST_ITEM, Id, OwnerPlayer, (int)QITEM_USE);
	}
	else //무기
	{
		if (IType == ItemType::ITEM_SWORD)
			NewItem = CreateWeapon(Id, WEAPONTYPE::WEAPON_SWORD);
		else// if (IType == ItemType::ITEM_BOW)
			NewItem = CreateWeapon(Id, WEAPONTYPE::WEAPON_ARROW);

		GainNewWeapon(NewItem, SlotIndex);
		GInstance->CheckQuest(QUEST_ITEM, Id, OwnerPlayer, (int)QITEM_EQUIP);
	}
	// 기타 아이템도 추가할 것
	NewItem->SetInventory(this);
	NewItem->SetCount(1);
	NewItem->SetOwner(Cast<AActor>(OwnerPlayer));

	
	
}


void UInventory::GainNewWeapon(AItem* Item, int SlotIndex)
{
	auto Weapon = Cast<AWeapon>(Item);
	if (Weapon == nullptr) return;

	if(Weapon->GetType() == WEAPONTYPE::WEAPON_SWORD)
		UE_LOG(LogTemp, Warning, TEXT("Sword Gain!"));
	if (Weapon->GetType() == WEAPONTYPE::WEAPON_ARROW)
		UE_LOG(LogTemp, Warning, TEXT("Bow Gain!"));

	int Index;
	if (SlotIndex == -1)
		Index = FindEmptySlotIndex(EquipItems);
	else
		Index = SlotIndex;

	if (Index == -1)
		return;//빈칸 없음
	Item->SetItemMesh();
	Item->SetSlotIndex(Index);
	EquipItems[Index] = Item;
	
}

void UInventory::GainNewUseItem(AItem* Item, int SlotIndex)
{
	auto UseItem = Cast<AUseItem>(Item);
	if (UseItem == nullptr) return;

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
		return;//빈칸 없음
	Item->SetSlotIndex(Index);
	UseItems[Index] = Item;
}

AWeapon* UInventory::CreateWeapon(int Id, WEAPONTYPE WType)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance()); // 나중에 Weapon Data 끌고오기 위함
	AWeapon* Weapon;
	if(WType == WEAPONTYPE::WEAPON_SWORD)
		Weapon = NewObject<ASword>();
	else
		Weapon = NewObject<ABow>();

	Weapon->SetId(Id);
	Weapon->SetWeaponType(WType);
	// 나중에 공격력 이런 정보들 다 여기서 세팅
	// WType에 따라 GInstance -> Data에 접근해서 무기 정보 가져오기
	return Weapon;
}

AUseItem* UInventory::CreateUseItem(int Id)
{
	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	AUseItem* UseItem = NewObject<AUseItem>();
	UseItem->SetId(Id);

	// 정보 세팅 + 못한 정보세팅 다 여기서
	UseItem->SetUseType(GInstance->GetUseItemData(Id)->Type);
	UseItem->SetAmount(GInstance->GetUseItemData(Id)->Amount);

	return UseItem;
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

void UInventory::AddGold(int Value)
{
	Gold += Value;

	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	auto Widget = Cast<UWidget_Inventory>(GInstance->GetUIMgr()->GetUI(UIType::Inventory));
	if (Widget != nullptr)
	{
		Widget->RefreshGoldText(OwnerPlayer);
	}
}

void UInventory::SpendGold(int Value)
{
	Gold -= Value;

	auto GInstance = Cast<UMyGameInstance>(OwnerPlayer->GetGameInstance());
	auto Widget = Cast<UWidget_Inventory>(GInstance->GetUIMgr()->GetUI(UIType::Inventory));
	if (Widget != nullptr)
	{
		Widget->RefreshGoldText(OwnerPlayer);
	}
}




