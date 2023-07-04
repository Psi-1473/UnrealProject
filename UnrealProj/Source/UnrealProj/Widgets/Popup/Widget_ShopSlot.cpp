// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ShopSlot.h"
#include "../../MyGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../Items/Item.h"
#include "../../Items/UseItem/UseItem.h"
#include "../../Items/Weapons/Weapon.h"

void UWidget_ShopSlot::ClickBuyButton()
{
	//if (IType == ITEM_USE)
	//{
	//	AUseItem* NewItem = CreateNewUseItem();
	//}
	//else
	//{
	//	AWeapon* NewItem = CreateNewWeapon();
	//}
	//Type = Use;
	//UseItems[1] = NewObject<AUseItem>();
	//UseItems[1]->SetId(1);
	//UseItems[1]->SetCount(1);
	//UseItems[1]->SetInventory(this);
}

void UWidget_ShopSlot::SetSlot(UMyGameInstance* GInstance, ItemType TemType, int16 Id)
{
	ItemId = Id;
	IType = TemType;

	FString Name;
	FString Price;

	if (TemType == ITEM_SWORD)
	{
		Name = GInstance->GetSwordData(Id)->Name;
		Price = FString::FromInt(GInstance->GetSwordData(Id)->Price);
		Img_Item->SetBrush(GInstance->GetSwordImage(Id)->Brush);
		WType = WEAPON_SWORD;
	}
	else if (TemType == ITEM_BOW)
	{
		Name = GInstance->GetBowData(Id)->Name;
		Price = FString::FromInt(GInstance->GetBowData(Id)->Price);
		Img_Item->SetBrush(GInstance->GetBowImage(Id)->Brush);
		WType = WEAPON_ARROW;
	}
	else if (TemType == ITEM_USE)
	{
		Name = GInstance->GetUseItemData(Id)->Name;
		Price = FString::FromInt(GInstance->GetUseItemData(Id)->Price);
		Img_Item->SetBrush(GInstance->GetUseItemImage(Id)->Brush);
	}

	Text_Name->SetText(FText::FromString(*Name));
	Text_Gold->SetText(FText::FromString(*Price));
}

AWeapon* UWidget_ShopSlot::CreateNewWeapon()
{
	AWeapon* Weapon = NewObject<AWeapon>();
	Weapon->SetId(ItemId);
	Weapon->SetWeaponType(WType);
	
	return Weapon;
}


AUseItem* UWidget_ShopSlot::CreateNewUseItem()
{
	AUseItem* UseItem = NewObject<AUseItem>();
	UseItem->SetId(ItemId);

	return UseItem;
}
