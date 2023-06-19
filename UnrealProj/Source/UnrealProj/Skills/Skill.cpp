// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"

void USkill::Execute(AActor* OwnerActor)
{
	if (!bCanUse)
		return;
}

void USkill::PlayParticle(AActor* OwnerActor)
{
}
