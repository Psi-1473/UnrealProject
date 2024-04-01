// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_BossHpBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "../../Stat/MonsterStatComponent.h"

void UWidget_BossHpBar::BindBoss(ABossMonster* Boss)
{
	BindedBoss = Boss;
	Text_Name->SetText(FText::FromString(Boss->GetStatComponent()->GetMonsterName()));
	
	Boss->GetStatComponent()->OnHpChanged.AddUObject(this, &UWidget_BossHpBar::SetHpBar);
}

void UWidget_BossHpBar::SetHpBar()
{
	PB_Hp->SetPercent(BindedBoss->GetStatComponent()->GetHpRatio());
}
