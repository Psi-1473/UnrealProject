// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ShopSlot.h"
#include "../../MyGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../Items/Item.h"
#include "../../Items/UseItem/UseItem.h"
#include "../../Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Inventory/Inventory.h"
#include "Components/Button.h"



void UWidget_ShopSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Buy->OnClicked.AddDynamic(this, &UWidget_ShopSlot::ClickBuyButton);
}

void UWidget_ShopSlot::ClickBuyButton()
{
	// 돈있나 확인 먼저

	AItem* NewItem;
	if (IType == ITEM_USE)NewItem = CreateNewUseItem();
	else NewItem = CreateNewWeapon();

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	MyPlayer->GetInventory()->GainNewItem(NewItem); // 나머지 세팅은 여기서
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
	Weapon->SetCount(1);
	Weapon->SetWeaponType(WType);
	
	return Weapon;
}


AUseItem* UWidget_ShopSlot::CreateNewUseItem()
{
	AUseItem* UseItem = NewObject<AUseItem>();
	UseItem->SetId(ItemId);
	UseItem->SetCount(1);

	return UseItem;
}
