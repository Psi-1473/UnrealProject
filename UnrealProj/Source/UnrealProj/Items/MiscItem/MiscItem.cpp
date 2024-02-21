// Fill out your copyright notice in the Description page of Project Settings.


#include "MiscItem.h"
#include "../../MyGameInstance.h"
#include "../../Widgets/Popup/Widget_Inventory.h"
#include "../../Inventory/Inventory.h"
#include "../../Creatures/Player/MyPlayer.h"

void AMiscItem::SetCount(int Value)
{
	Super::SetCount(Value);
	Count = Value;
	auto GInstance = Cast<UMyGameInstance>(Inventory->GetPlayer()->GetInstance());
	auto Inven = GInstance->GetUIMgr()->GetUI(UIType::Inventory);

	if (Count == 0)
	{
		Inventory->EmptySlot(Inventory->GetMiscItems(), SlotIndex);
	}

	if (Inven != nullptr)
	{
		auto InvenWidget = Cast<UWidget_Inventory>(Inven);
		InvenWidget->RefreshSlotByIndex(SlotIndex);
	}
}

FRichImageRow* AMiscItem::GetItemImage(UMyGameInstance* GInstance)
{
	return GInstance->GetMiscItemImage(Id);
}
