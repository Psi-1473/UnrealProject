// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Inventory.h"
#include "Widget_InvenSlot.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Inventory/Inventory.h"
#include "../../Items/Item.h"
#include "Widget_InvenSlot.h"
#include "Components/Button.h"

void UWidget_Inventory::NativeConstruct()
{
	CreateSlot();
	Btn_Equip->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeEquip);
	Btn_Use->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeUse);
	Btn_Etc->OnClicked.AddDynamic(this, &UWidget_Inventory::SetInventoryTypeEtc);
}

void UWidget_Inventory::CreateSlot()
{
	// 실행이 안된다 블루프린트에서 부모 설정안한듯
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
}


void UWidget_Inventory::SetInventoryTypeEquip()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	MyPlayer->GetInventory()->SetType(InventoryType::Equip);
	UpdateSlotInfo();
}

void UWidget_Inventory::SetInventoryTypeUse()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	MyPlayer->GetInventory()->SetType(InventoryType::Use);
	UpdateSlotInfo();
}

void UWidget_Inventory::SetInventoryTypeEtc()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	MyPlayer->GetInventory()->SetType(InventoryType::Etc);
	UpdateSlotInfo();
}
