// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_Third.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Texture2D.h"
#include "../../../Helpers/AttackChecker.h"
#include "../../../CameraShakes/SkillHitCameraShake.h"

UPlayerSkill_Sword_Third::UPlayerSkill_Sword_Third()
{
	bRange = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle1(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Ultimate_Warmup.P_Aurora_Ultimate_Warmup'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Ultimate_InitialBlast.P_Aurora_Ultimate_InitialBlast'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle3(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Ultimate_Explode_Cheap.P_Aurora_Ultimate_Explode_Cheap'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Sword3.Sword3'"));
	static ConstructorHelpers::FClassFinder<USkillHitCameraShake> SHAKE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/CameraShakes/Player/Skill/Sword/BP_Shake_Sword3.BP_Shake_Sword3_C'"));


	if(Particle1.Succeeded()) PreParticle = Particle1.Object;
	if(Particle2.Succeeded()) AttackParticle = Particle2.Object;
	if(Particle3.Succeeded()) HitEffect = Particle3.Object;
	if(IMG.Succeeded()) Txt = IMG.Object;
	if (SHAKE.Succeeded()) CameraShake = SHAKE.Class;

	

}

void UPlayerSkill_Sword_Third::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	if (RemainingTime > 0.f)
		return;
	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	SetDefaultValue();


	OwnerPlayer->LaunchCharacter(OwnerPlayer->GetActorUpVector() * 700.f, true, true);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PreParticle, OwnerPlayer->GetActorLocation());
}

void UPlayerSkill_Sword_Third::PlayParticle(AActor* OwnerActor)
{

	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), AttackParticle, OwnerPlayer->GetActorLocation());

	TArray<FOverlapResult> Mobs;
	Mobs = UAttackChecker::PlayerCircleCheck(OwnerPlayer->GetActorLocation(), 800.f, 800.f, ECC_GameTraceChannel5, OwnerActor);
	UAttackChecker::ApplyOverlapDamageToActors(10.f, OwnerActor, Mobs, HitEffect);
	
	OwnerPlayer->ShakeCamera(CameraShake);

}
