// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_PlayerMain.h"
#include "Components/HorizontalBox.h"
#include "Widget_QuickSlot.h"
#include "Widget_SkillQuick.h"
#include "Widget_ItemQuick.h"
#include "../DEFINE.h"
#include "Components/TextBlock.h"

const int SkillSlotCount = 3;
const int ItemSlotCount = 3;

void UWidget_PlayerMain::NativeConstruct()
{
	SetSkillQuick();
	SetItemQuick();
}

void UWidget_PlayerMain::SetSkillQuick()
{
	for (int i = 0; i < SkillSlotCount; i++)
	{
		auto SkillQuick = Cast<UWidget_SkillQuick>(SkillBox->GetChildAt(i));
		SkillQuickSlots.Add(SkillQuick);
		
		// 0 - Q
		// 1 - E
		// 2 - R
	}
	//SkillQuickSlots[KEY_Q]->GetTextKey()->SetText(FText::FromString(*TEXT("Q")));
	//SkillQuickSlots[KEY_E]->GetTextKey()->SetText(FText::FromString(*TEXT("E")));
	//SkillQuickSlots[KEY_R]->GetTextKey()->SetText(FText::FromString(*TEXT("R")));
}

void UWidget_PlayerMain::SetItemQuick()
{
	for (int i = 0; i < SkillSlotCount; i++)
	{
		auto ItemQuick = Cast<UWidget_ItemQuick>(SkillBox->GetChildAt(i));
		ItemQuickSlots.Add(ItemQuick);
		//ItemQuickSlots[i]->GetTextKey()->SetText(FText::FromString(*FString::FromInt(i+1)));
		// 0 - 1
		// 1 - 2
		// 2 - 3
	}
}
