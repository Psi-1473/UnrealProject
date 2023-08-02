// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Fourth.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

USevarogSkill_Fourth::USevarogSkill_Fourth()
{
	Id = 4;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SiphonTargeting.P_SiphonTargeting'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SoulSwirlsBody.P_SoulSwirlsBody'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST3(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SoulSwirls.P_SoulSwirls'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_GhostHand.P_GhostHand'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SiphonImpact.P_SiphonImpact'"));
	if (CAST.Succeeded())
		CastEffect = CAST.Object;
	if (CAST2.Succeeded())
		CastEffect2 = CAST2.Object;
	if (CAST3.Succeeded())
		CastEffect3 = CAST3.Object;
	if (ATTACK.Succeeded())
		AttackEffect = ATTACK.Object;
	if (ATTACK2.Succeeded())
		AttackEffect2 = ATTACK2.Object;
}

void USevarogSkill_Fourth::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	Boss->SetExecutingSkill(this);
	PlaySkillEffect();
}

void USevarogSkill_Fourth::PlaySkillEffect()
{
	FTransform Trans = OwnerMonster->GetActorTransform();
	CastingEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect2, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect3, Trans);
}

void USevarogSkill_Fourth::Attack()
{
	FTransform Trans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), AttackEffect, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), AttackEffect2, Trans);
	CastingEffectComponent->DestroyComponent();

	// 히트 체크
}
