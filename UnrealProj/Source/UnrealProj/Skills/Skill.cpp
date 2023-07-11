// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Animations/Player/PlayerAnim.h"
#include "../Items/Weapons/Weapon.h"
#include "EffectActor//SkillEffectActor.h"
#include "EffectActor//SkillRangeActor.h"
#include "../State/CharacterState.h"
#include "Components/Image.h"

void USkill::SetDefaultValue()
{
	OwnerPlayer->SetState(STATE::SKILL);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
}

void USkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	if (!bCanUse)
		return;

	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);

	if (OwnerPlayer == nullptr)
		return;

	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	if (!bRangeAttack)
		OwnerPlayer->SetState(STATE::SKILLCAST);
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

void USkill::CancleCast(AActor* OwnerActor)
{
	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);
	OwnerPlayer->GetAnimInst()->SetBowCast(false);
	OwnerPlayer->SetState(STATE::IDLE);
	if (OwnerPlayer->GetSpawnedRangeActor())
	{
		OwnerPlayer->GetSpawnedRangeActor()->Destroy();
		OwnerPlayer->SetRangeActor(nullptr);
	}
}

void USkill::CastToExecute(AActor* OwnerActor)
{
	
}

FSkillData* USkill::GetSkillInfo()
{
	if (WeaponType == WEAPONTYPE::WEAPON_SWORD)
		return OwnerPlayer->GetInstance()->GetSwordSkillData(Id);
	else
		return OwnerPlayer->GetInstance()->GetBowSkillData(Id);
}

