// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../Projectiles/Projectile.h"

UPlayerSkill_Bow_Second::UPlayerSkill_Bow_Second()
{
	Id = 2;
	WeaponType = WEAPON_ARROW;
	bRange = false;
}

void UPlayerSkill_Bow_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	SetDefaultValue();
}

void UPlayerSkill_Bow_Second::PlayParticle(AActor* OwnerActor)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerPlayer;
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerPlayer->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation.Pitch += 5.f;

	float RotYaw[5] = { -10, -5, 0, 5, 10 };

	for (int i = 0; i < 5; i++)
	{
		AProjectile* Projectile = OwnerPlayer->GetWorld()->SpawnActor<AProjectile>(OwnerPlayer->GetWeapon()->GetArrow(),
			OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorUpVector() * 55.f,
			CameraRotation + FRotator(0.f, RotYaw[i], 0.f),
			SpawnParams);

		Projectile->FireInDirection(Projectile->GetActorForwardVector(), 2.f);
	}
}
