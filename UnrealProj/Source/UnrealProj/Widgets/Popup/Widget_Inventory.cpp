// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Inventory.h"
#include "Widget_InvenSlot.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Inventory/Inventory.h"
#include "../../Items/Item.h"
#include "Widget_InvenSlot.h"

void UWidget_Inventory::NativeConstruct()
{
	CreateSlot();
}

void UWidget_Inventory::CreateSlot()
{
	// 실행이 안된다 블루프린트에서 부모 설정안한듯
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	
	for(int i = 0; i < SlotBox->GetChildrenCount(); i++)
	{
		Slots.Add(Cast<UWidget_InvenSlot>(SlotBox->GetChildAt(i)));
		Slots[i]->SetItem(MyPlayer->GetInventory()->GetInventory()[i]);

		Slots[i]->SetImage();
		Slots[i]->SetCount();
	}
	//RefreshSlot(TypeIndex);
}