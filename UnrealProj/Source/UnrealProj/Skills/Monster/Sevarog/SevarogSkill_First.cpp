// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_First.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Animations/Monster/BossAnimInstance.h"

USevarogSkill_First::USevarogSkill_First()
{
	Id = 1;
}

void USevarogSkill_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(true);
	// * 기모으는 이펙트 켜기
	OwnerMonster->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, this, &USevarogSkill_First::Swing, 3.f, false);
}

void USevarogSkill_First::Swing()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	// * 기모으는 이펙트 끄기
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	OwnerMonster->GetWorldTimerManager().ClearTimer(ExecuteTimerHandle);
}
