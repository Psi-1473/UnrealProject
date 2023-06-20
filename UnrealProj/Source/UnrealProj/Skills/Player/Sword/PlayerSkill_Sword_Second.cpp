// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"

UPlayerSkill_Sword_Second::UPlayerSkill_Sword_Second()
{
	Id = 2;
}

void UPlayerSkill_Sword_Second::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
	
}

void UPlayerSkill_Sword_Second::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);

	if (Effect == nullptr)
		return;
}
