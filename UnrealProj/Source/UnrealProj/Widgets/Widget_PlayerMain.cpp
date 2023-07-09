// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_PlayerMain.h"
#include "Components/HorizontalBox.h"
#include "Widget_QuickSlot.h"
#include "Widget_SkillQuick.h"
#include "Widget_ItemQuick.h"
#include "../DEFINE.h"
#include "Components/TextBlock.h"
#include "../Items/Item.h"
#include "../Skills/Skill.h"
#include "../Skills/Components/PlayerSkillComponent.h"

const int SkillSlotCount = 3;
const int ItemSlotCount = 3;

void UWidget_PlayerMain::NativeConstruct()
{
	SetSkillQuick();
	SetItemQuick();
}

void UWidget_PlayerMain::SwapSkillQuickSlot(UPlayerSkillComponent* SkillComponent, int From, int To)
{
	USkill* Skill = SkillQuickSlots[From]->GetSkill();
	SkillQuickSlots[From]->SetSkill(SkillQuickSlots[To]->GetSkill());
	SkillQuickSlots[From]->SetImage();
	SkillQuickSlots[To]->SetSkill(Skill);
	SkillQuickSlots[To]->SetImage();
	// 등록된 키 변경 (완)
	SkillComponent->RegisterSkill(From, SkillQuickSlots[From]->GetSkill());
	SkillComponent->RegisterSkill(To, SkillQuickSlots[To]->GetSkill());
	
}

void UWidget_PlayerMain::SwapItemQuickSlot(int From, int To)
{
	AItem* Item = ItemQuickSlots[From]->GetItem();
	ItemQuickSlots[From]->SetItem(ItemQuickSlots[To]->GetItem());
	ItemQuickSlots[From]->SetImage();
	ItemQuickSlots[To]->SetItem(Item);
	ItemQuickSlots[To]->SetImage();
	// 등록된 키도 변경
}

void UWidget_PlayerMain::PressQuickSlot(int Index)
{
	ItemQuickSlots[Index]->UseItem();
}

void UWidget_PlayerMain::SetSkillQuick()
{
	for (int i = 0; i < SkillSlotCount; i++)
	{
		auto SkillQuick = Cast<UWidget_SkillQuick>(SkillBox->GetChildAt(i));
		SkillQuickSlots.Add(SkillQuick);
		SkillQuickSlots[i]->SetSlotIndex(i);
		SkillQuickSlots[i]->SetMainWidget(this);
		// 0 - Q
		// 1 - E
		// 2 - R
	}
	SkillQuickSlots[KEY_Q]->GetTextKey()->SetText(FText::FromString(TEXT("Q")));
	SkillQuickSlots[KEY_E]->GetTextKey()->SetText(FText::FromString(TEXT("E")));
	SkillQuickSlots[KEY_R]->GetTextKey()->SetText(FText::FromString(TEXT("R")));
}

void UWidget_PlayerMain::SetItemQuick()
{
	for (int i = 0; i < SkillSlotCount; i++)
	{
		auto ItemQuick = Cast<UWidget_ItemQuick>(ItemBox->GetChildAt(i));
		ItemQuickSlots.Add(ItemQuick);
		ItemQuickSlots[i]->SetSlotIndex(i);
		ItemQuickSlots[i]->GetTextKey()->SetText(FText::FromString(FString::FromInt(i+1)));
		ItemQuickSlots[i]->SetMainWidget(this);
		 //0 - 1
		 //1 - 2
		 //2 - 3
	}
}
