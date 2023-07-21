// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../EffectActor//SkillRangeActor.h"
#include "../../Items/Weapons/Weapon.h"

void UPlayerSkill::SetDefaultValue()
{
	OwnerPlayer->SetState(STATE::SKILL);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
}

void UPlayerSkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);

	if (OwnerPlayer == nullptr)
		return;

	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	if (!bRangeAttack)
		OwnerPlayer->SetState(STATE::SKILLCAST);
}

void UPlayerSkill::CancleCast(AActor* OwnerActor)
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


FSkillData* UPlayerSkill::GetSkillInfo()
{
	if (WeaponType == WEAPONTYPE::WEAPON_SWORD)
		return OwnerPlayer->GetInstance()->GetSwordSkillData(Id);
	else
		return OwnerPlayer->GetInstance()->GetBowSkillData(Id);
}
