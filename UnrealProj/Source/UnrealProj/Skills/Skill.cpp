// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "../Creatures/Player/MyPlayer.h"
#include "EffectActor//SkillEffectActor.h"
#include "../State/CharacterState.h"

void USkill::Execute(AActor* OwnerActor)
{
	if (!bCanUse)
		return;

	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);

	if (OwnerPlayer == nullptr)
		return;
}

void USkill::PlayParticle(AActor* OwnerActor)
{
}

void USkill::DestroyActor()
{
	if (EffectActor == nullptr)
		return;

	EffectActor->Destroy();
}
