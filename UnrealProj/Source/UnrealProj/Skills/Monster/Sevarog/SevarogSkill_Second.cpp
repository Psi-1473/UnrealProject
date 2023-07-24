// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Second.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

USevarogSkill_Second::USevarogSkill_Second()
{
	Id = 2;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Subjugate/FX/P_Sub_Cast.P_Sub_Cast'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_SoulStageEmbers.P_SoulStageEmbers'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Subjugate/FX/P_SubjugateSwirls.P_SubjugateSwirls'"));
	if (CAST.Succeeded()) CastEffect = CAST.Object;
	if (CAST2.Succeeded()) CastEffect2 = CAST2.Object;
	if (FIRE.Succeeded()) FireEffect = FIRE.Object;
}

void USevarogSkill_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	TargetPos = Boss->GetTarget()->GetActorLocation();
	PlaySkillEffect();
}

void USevarogSkill_Second::PlaySkillEffect()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(true);
	Boss->SetExecutingSkill(this);
	FTransform Trans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect, Trans);
	FTransform TargetTrans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect2, TargetTrans);
}

void USevarogSkill_Second::Attack()
{
	FTransform Trans(TargetPos);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), FireEffect, Trans);

	// 히트 체크
}
