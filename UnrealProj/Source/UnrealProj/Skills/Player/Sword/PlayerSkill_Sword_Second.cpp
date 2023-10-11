// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../EffectActor/SkillEffectActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../EffectActor/Player/SEA_Sword_SecondDash.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "../../../CameraShakes/SkillHitCameraShake.h"

UPlayerSkill_Sword_Second::UPlayerSkill_Sword_Second()
{
	bRange = false;

	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/0/BP_Effect_0_2_Dash.BP_Effect_0_2_Dash_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PP(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Spawn.P_Aurora_Decoy_Spawn'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DP(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Explode_Fragments.P_Aurora_Decoy_Explode_Fragments'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Sword2.Sword2'"));
	static ConstructorHelpers::FClassFinder<USkillHitCameraShake> SHAKE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/CameraShakes/Player/Skill/Sword/BP_Shake_Sword2.BP_Shake_Sword2_C'"));


	if (EFFECT.Succeeded()) Effect = EFFECT.Class;
	if (PP.Succeeded()) PlayerParticle = PP.Object;
	if (DP.Succeeded()) DestroyParticle = DP.Object;
	if (IMG.Succeeded()) Txt = IMG.Object;
	if (SHAKE.Succeeded()) CameraShake = SHAKE.Class;
}

void UPlayerSkill_Sword_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (RemainingTime > 0.f)
		return;
	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	MoveDir = OwnerActor->GetActorForwardVector();
	OwnerPlayer->bUseControllerRotationYaw = false;
	SetDefaultValue();
	MoveDir = OwnerActor->GetActorForwardVector();
	OwnerPlayer->ShakeCamera(CameraShake);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, OwnerPlayer->GetActorLocation());
}

void UPlayerSkill_Sword_Second::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);

	if (Effect == nullptr)
		return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetActorLocation();

	EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
	EffectActor->SetOwner(Cast<AActor>(OwnerPlayer));
}

void UPlayerSkill_Sword_Second::DestroyActor()
{
	Super::DestroyActor();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), DestroyParticle, OwnerPlayer->GetActorLocation());
}
