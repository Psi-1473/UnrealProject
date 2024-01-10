// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../MyGameInstance.h"
#include "../../../CameraShakes/SkillHitCameraShake.h"
#include "../../../CameraShakes/CameraEffectComponent.h"

UPlayerSkill_Sword_First::UPlayerSkill_Sword_First()
{
	//Id = 1;
	//WeaponType = WEAPONTYPE::WEAPON_SWORD;
	bRange = false;
	//Name = TEXT("Sword 1");

	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/0/BP_Effect_0_1.BP_Effect_0_1_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE_Player(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Whrilwind.P_Aurora_Freeze_Whrilwind'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Swrod1.Swrod1'"));
	static ConstructorHelpers::FClassFinder<USkillHitCameraShake> SHAKE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/CameraShakes/Player/Skill/Sword/BP_Shake_Sword1.BP_Shake_Sword1_C'"));

	
	if (EFFECT.Succeeded()) Effect = EFFECT.Class;
	if (PARTICLE_Player.Succeeded()) PlayerParticle = PARTICLE_Player.Object;
	if (IMG.Succeeded()) Txt = IMG.Object;
	if (SHAKE.Succeeded()) CameraShake = SHAKE.Class;
	
}

void UPlayerSkill_Sword_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (RemainingTime > 0.f)
		return;

	SetDefaultValue();
}

void UPlayerSkill_Sword_First::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);
	
	if (Effect == nullptr)
		return;
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, OwnerPlayer->GetActorLocation());
	SetParticleTimer();
	OwnerPlayer->GetCameraEffectComponent()->ShakeCameraByClass(CameraShake);
}

void UPlayerSkill_Sword_First::SetParticleTimer()
{
	if (SpawnCount < MaxSpawnCount)
	{
		if (OwnerPlayer == nullptr)
			return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
		SpawnParams.Instigator = OwnerPlayer->GetInstigator();

		FRotator SpawnRot = OwnerPlayer->GetActorRotation() + FRotator(0.f, RotZ[SpawnCount], 0.f);
		FVector SpawnPos = OwnerPlayer->GetActorLocation() - FVector(0.f, 0.f, 50.f);
		SpawnPos += OwnerPlayer->GetActorForwardVector() * LocX[SpawnCount];
		SpawnPos += OwnerPlayer->GetActorRightVector() * LocY[SpawnCount];
		EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
		EffectActor->SetOwner(Cast<AActor>(OwnerPlayer));
		SpawnCount++;
		OwnerPlayer->GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &UPlayerSkill_Sword_First::SetParticleTimer, 0.05f, true);
	}
	else
	{
		SpawnCount = 0;
		OwnerPlayer->GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

