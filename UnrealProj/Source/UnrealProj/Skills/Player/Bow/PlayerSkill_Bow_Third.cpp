// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_Third.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../Projectiles/Projectile.h"

void UPlayerSkill_Bow_Third::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (RemainingTime > 0.f)
		return;

	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;


}

void UPlayerSkill_Bow_Third::PlayParticle(AActor* OwnerActor)
{
}
