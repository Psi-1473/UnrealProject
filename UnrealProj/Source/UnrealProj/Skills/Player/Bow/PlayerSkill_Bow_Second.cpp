// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../Inventory/EquipItemComponent.h"
#include "../../../Projectiles/Projectile.h"
#include "../../../CameraShakes/SkillHitCameraShake.h"
#include "../../../CameraShakes/CameraEffectComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"


UPlayerSkill_Bow_Second::UPlayerSkill_Bow_Second()
{
	//Id = 2;
	//WeaponType = WEAPONTYPE::WEAPON_ARROW;
	bRange = false;
	//Name = TEXT("Bow 2");
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_Burst.P_Sparrow_Burst'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Arrow1.Arrow1'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_PROTO_Proto_Ballistic_HitWorld.P_PROTO_Proto_Ballistic_HitWorld'"));
	static ConstructorHelpers::FClassFinder<USkillHitCameraShake> SHAKE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/CameraShakes/Player/Skill/Bow/BP_Shake_Bow2.BP_Shake_Bow2_C'"));

	
	if (PParticle.Succeeded()) PlayerParticle = PParticle.Object;
	if (IMG.Succeeded()) Txt = IMG.Object;
	if (HIT.Succeeded()) HitEffect = HIT.Object;
	if (SHAKE.Succeeded()) CameraShake = SHAKE.Class;
}

void UPlayerSkill_Bow_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	
	Super::Execute(OwnerActor, bRangeAttack);

	if (RemainingTime > 0.f)
		return;

	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, OwnerPlayer->GetActorLocation());
	SetDefaultValue();
}

void UPlayerSkill_Bow_Second::PlayParticle(AActor* OwnerActor)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerPlayer->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation.Pitch += 5.f;
	
	FRotator Rot = OwnerPlayer->GetActorRotation();

	FString Directory = TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Skins/Rogue/P_Sparrow_UltArrow.P_Sparrow_UltArrow'");
	UParticleSystem* Particle = LoadObject<UParticleSystem>(NULL, *Directory, NULL, LOAD_None, NULL);

	float RotYaw[5] = { -8, -4, 0, 4, 8 };

	AWeapon* Weapon = OwnerPlayer->GetEquipComponent()->GetWeapon();
	for (int i = 0; i < 5; i++)
	{
		AProjectile* Projectile = OwnerPlayer->GetWorld()->SpawnActor<AProjectile>(Weapon->GetArrow(),
			OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorUpVector() * 55,
			Rot + FRotator(0.f, RotYaw[i], 0.f),
			SpawnParams);
		if (Projectile == nullptr)
			return;
		Projectile->SetAttackStrength(true);
		Projectile->SetHitEffect(HitEffect);
		Projectile->SetMaxSpeed(6000.f);
		Projectile->SetLifeSpan(0.5f);
		Projectile->SetParticle(Particle);
		Projectile->FireInDirection(Projectile->GetActorForwardVector(), 2.f);
	}
	OwnerPlayer->GetCameraEffectComponent()->ShakeCameraByClass(CameraShake);
}
