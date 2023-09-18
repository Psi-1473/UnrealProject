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
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	if (MyPlayer->GetInventory()->GetGold() < ItemPrice)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Enough Gold"));
		return;
	}
	MyPlayer->GetInventory()->SpendGold(ItemPrice);
	MyPlayer->GetInventory()->GainNewItem(IType, ItemId);
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
		ItemPrice = GInstance->GetSwordData(Id)->Price;
		Img_Item->SetBrush(GInstance->GetSwordImage(Id)->Brush);
		WType = WEAPONTYPE::WEAPON_SWORD;
	}
	else if (TemType == ITEM_BOW)
	{
		Name = GInstance->GetBowData(Id)->Name;
		ItemPrice = GInstance->GetBowData(Id)->Price;
		Img_Item->SetBrush(GInstance->GetBowImage(Id)->Brush);
		WType = WEAPONTYPE::WEAPON_ARROW;
	}
	else if (TemType == ITEM_USE)
	{
		Name = GInstance->GetUseItemData(Id)->Name;
		ItemPrice = GInstance->GetUseItemData(Id)->Price;
		Img_Item->SetBrush(GInstance->GetUseItemImage(Id)->Brush);
	}

	Price = FString::FromInt(ItemPrice);
	Text_Name->SetText(FText::FromString(*Name));
	Text_Gold->SetText(FText::FromString(*Price));
}





