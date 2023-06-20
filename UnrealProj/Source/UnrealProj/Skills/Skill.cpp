// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "../Creatures/Player/MyPlayer.h"

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
