// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../DEFINE.h"
#include "../../../State/CharacterState.h"

UPlayerSkill_Bow_First::UPlayerSkill_Bow_First()
{
	Id = 1;
	WeaponType = WEAPON_ARROW;

}

void UPlayerSkill_Bow_First::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);

	if (OwnerPlayer->GetState() == OwnerPlayer->GetSpecificState(STATE::ATTACK))
		return;

	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->SetBowCast(true);
	//OwnerPlayer->SetState(STATE::SKILLCAST);
	// 조준상태로
}

void UPlayerSkill_Bow_First::PlayParticle(AActor* OwnerActor)
{
}

void UPlayerSkill_Bow_First::DestroyActor()
{
}

void UPlayerSkill_Bow_First::CastToExecute(AActor* OwnerActor)
{
	Super::CastToExecute(OwnerActor);
	OwnerPlayer->SetState(STATE::SKILL);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
}
