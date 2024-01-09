// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Inventory.h"
#include "Widget_InvenSlot.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Inventory/Inventory.h"
#include "../../Items/Item.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Managers/UIManager.h"
#include "Widget_InvenSlot.h"
#include "Components/Button.h"
#include "../../Inventory/EquipItemComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidget_Inventory::NativeConstruct()
{
	CreateSlot();
	Btn_Equip->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeEquip);
	Btn_Use->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeUse);
	Btn_Etc->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeEtc);
}

void UWidget_Inventory::CreateSlot()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	for (int i = 0; i < SlotBox->GetChildrenCount(); i++)
	{
		Slots.Add(Cast<UWidget_InvenSlot>(SlotBox->GetChildAt(i)));
		Slots[i]->SetInvenWidget(this);
	}

	UpdateSlotInfo();
}

void UWidget_Inventory::UpdateSlotInfo()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	for (int i = 0; i < SlotBox->GetChildrenCount(); i++)
	{
		Slots[i]->SetItem(MyPlayer->GetInventory()->GetInventory()[i]);
		Slots[i]->SetImage();
		Slots[i]->SetCount();
		Slots[i]->SetSlotIndex(i);
	}
	Img_EquipWeapon->SetBrush(MyPlayer->GetEquipComponent()->GetWeapon()->GetItemImage(MyPlayer->GetInstance())->Brush);
	RefreshGoldText(MyPlayer);
}

void UWidget_Inventory::RefreshSlotByIndex(int SlotIndex)
{
	Slots[SlotIndex]->RefreshSlot();
}

void UWidget_Inventory::RefreshGoldText(TWeakObjectPtr<class AMyPlayer> Player)
{
	FString GoldText = TEXT("Gold : ") + FString::FromInt(Player->GetInventory()->GetGold());
	Text_Gold->SetText(FText::FromString(GoldText));
}

void UWidget_Inventory::SetEquipWeaponImage(FRichImageRow* Image)
{
	Img_EquipWeapon->SetBrush(Image->Brush);
}


void UWidget_Inventory::SetInventoryTypeEquip()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	GInstance->GetUIMgr()->PlayButtonSound();
	MyPlayer->GetInventory()->SetType(InventoryType::Equip);
	UpdateSlotInfo();
}

void UWidget_Inventory::SetInventoryTypeUse()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	GInstance->GetUIMgr()->PlayButtonSound();
	MyPlayer->GetInventory()->SetType(InventoryType::Use);
	UpdateSlotInfo();
}

void UWidget_Inventory::SetInventoryTypeEtc()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	auto GInstance = Cast<UMyGameInstance>(MyPlayer->GetGameInstance());
	GInstance->GetUIMgr()->PlayButtonSound();
	MyPlayer->GetInventory()->SetType(InventoryType::Etc);
	UpdateSlotInfo();
}
