// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../Projectiles/Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

UPlayerSkill_Bow_Second::UPlayerSkill_Bow_Second()
{
	Id = 2;
	WeaponType = WEAPON_ARROW;
	bRange = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_Burst.P_Sparrow_Burst'"));

	if (PParticle.Succeeded())
		PlayerParticle = PParticle.Object;

	

}

void UPlayerSkill_Bow_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, OwnerPlayer->GetActorLocation());
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
	
	FRotator Rot = OwnerPlayer->GetActorRotation();

	FString Directory = TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Skins/Rogue/P_Sparrow_UltArrow.P_Sparrow_UltArrow'");
	UParticleSystem* Particle = LoadObject<UParticleSystem>(NULL, *Directory, NULL, LOAD_None, NULL);

	float RotYaw[5] = { -8, -4, 0, 4, 8 };

	for (int i = 0; i < 5; i++)
	{
		AProjectile* Projectile = OwnerPlayer->GetWorld()->SpawnActor<AProjectile>(OwnerPlayer->GetWeapon()->GetArrow(),
			OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorUpVector() * 55,
			Rot + FRotator(0.f, RotYaw[i], 0.f),
			SpawnParams);
		if (Projectile == nullptr)
			return;
		Projectile->SetAttackStrength(true);
		Projectile->SetParticle(Particle);
		Projectile->SetMaxSpeed(6000.f);
		Projectile->FireInDirection(Projectile->GetActorForwardVector(), 2.f);
	}
}
