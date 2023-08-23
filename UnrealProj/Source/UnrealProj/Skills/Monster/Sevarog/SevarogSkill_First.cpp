// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_First.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../EffectActor/SkillRangeActor.h"

USevarogSkill_First::USevarogSkill_First()
{
	Id = 1;
	CoolTime = 10.f;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EFFECT (TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Ultimate/FX/P_UltimateLooping.P_UltimateLooping'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SWING (TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Ultimate/FX/P_UltMeshArc_Expanding.P_UltMeshArc_Expanding'"));
	if (EFFECT.Succeeded())
		SkillEffect = EFFECT.Object;
	if (SWING.Succeeded())
		SwingEffect = SWING.Object;
}

void USevarogSkill_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(true);
	Boss->SetExecutingSkill(this);
	// * 기모으는 이펙트 켜기
	FTransform Trans = OwnerMonster->GetActorTransform();
	CastingEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), SkillEffect, Trans);
	OwnerMonster->GetWorldTimerManager().SetTimer(ExecuteTimerHandle, this, &USevarogSkill_First::Swing, 3.f, false);
}

void USevarogSkill_First::IndicateRange()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	SpawnParams.Instigator = OwnerMonster->GetInstigator();

	FRotator SpawnRot = OwnerMonster->GetActorRotation();
	FVector SpawnPos = OwnerMonster->GetActorLocation() * FVector(1.f, 1.f, 0.f);

	ASkillRangeActor* RangeActor = OwnerMonster->GetWorld()->SpawnActor<ASkillRangeActor>(
		ASkillRangeActor::StaticClass(), 
		SpawnPos, 
		SpawnRot, 
		SpawnParams);

	RangeActor->SetRange(Cast<AActor>(OwnerMonster), true, 3, 90.f);
	//OwnerMonster->SetRangeActor(RangeActor);
}

void USevarogSkill_First::PlaySkillEffect()
{
	FVector EffectVector = OwnerMonster->GetActorLocation();
	EffectVector.Z = 0;
	FTransform Trans(OwnerMonster->GetActorTransform());
	Trans.SetLocation(EffectVector);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), SwingEffect, Trans);
}

void USevarogSkill_First::Attack()
{

}

void USevarogSkill_First::Swing()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	// * 기모으는 이펙트 끄기
	// 스윙하는 이펙트 켜기
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	CastingEffectComponent->DestroyComponent();
	OwnerMonster->GetWorldTimerManager().ClearTimer(ExecuteTimerHandle);
	OwnerMonster->GetWorldTimerManager().SetTimer(CoolTimeHandler, this, &UMonsterSkill::EndCoolDown, CoolTime, false);


}
