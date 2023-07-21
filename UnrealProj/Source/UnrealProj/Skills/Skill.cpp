// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "EffectActor//SkillEffectActor.h"
#include "EffectActor//SkillRangeActor.h"
#include "../State/CharacterState.h"
#include "Components/Image.h"

void USkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	if (!bCanUse)
		return;
}

void USkill::DestroyActor()
{
	if (EffectActor == nullptr)
		return;

	EffectActor->Destroy();
}


