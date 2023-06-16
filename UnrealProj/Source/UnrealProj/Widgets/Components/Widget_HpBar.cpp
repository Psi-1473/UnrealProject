// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_HpBar.h"
#include "../../Stat/MonsterStatComponent.h"
#include "Components/ProgressBar.h"

void UWidget_HpBar::BindHp(UMonsterStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UWidget_HpBar::UpdateHp);
}

void UWidget_HpBar::UpdateHp()
{
	if(CurrentStatComp.IsValid())
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
}
