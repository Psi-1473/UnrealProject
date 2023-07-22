// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_First.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

USevarogSkill_First::USevarogSkill_First()
{
	Id = 1;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EFFECT (TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_ShadowTrails.P_ShadowTrails'"));
	if (EFFECT.Succeeded())
		SkillEffect = EFFECT.Object;
}

void USevarogSkill_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(true);
	// * 기모으는 이펙트 켜기
	FTransform Trans = OwnerMonster->GetActorTransform();
	CastingEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), SkillEffect, Trans);
	OwnerMonster->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, this, &USevarogSkill_First::Swing, 3.f, false);
}

void USevarogSkill_First::Swing()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	// * 기모으는 이펙트 끄기
	// 스윙하는 이펙트 켜기
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	CastingEffectComponent->DestroyComponent();
	OwnerMonster->GetWorldTimerManager().ClearTimer(ExecuteTimerHandle);
}
