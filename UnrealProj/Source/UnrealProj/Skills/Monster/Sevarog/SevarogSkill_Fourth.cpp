// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Fourth.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../EffectActor/SkillRangeActor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Engine/DamageEvents.h"
#include "../../../Helpers/AttackChecker.h"

USevarogSkill_Fourth::USevarogSkill_Fourth()
{
	Id = 4;
	CoolTime = 15.f;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SiphonTargeting.P_SiphonTargeting'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SoulSwirlsBody.P_SoulSwirlsBody'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST3(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SoulSwirls.P_SoulSwirls'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_GhostHand.P_GhostHand'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ATTACK2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SiphonImpact.P_SiphonImpact'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BLINK(TEXT("/Script/Niagara.NiagaraSystem'/Game/BlinkAndDashVFX/VFX_Niagara/NS_Curse_Blink.NS_Curse_Blink'"));
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
	if (ATTACK2.Succeeded())
		BlinkEffect = BLINK.Object;
}

void USevarogSkill_Fourth::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	// 1. Invisible ���·� ����� �� �ڸ��� ����Ʈ
	Boss->SetActorHiddenInGame(true);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(Boss->GetWorld(), 
		BlinkEffect, 
		Boss->GetActorLocation(), 
		Boss->GetActorRotation());
	
	// 2. 0.5�� �� �÷��̾� �ڷ� �̵� ��Ų��. �̵� �Ϸ��� ���� ���̸�?
	Boss->GetWorldTimerManager().SetTimer(BlinkTimer, this, &USevarogSkill_Fourth::Teleport, 0.5f, false);
	// 3. 0.3�� �� �ؿ� 3�� ����

}

void USevarogSkill_Fourth::AttackOrSpawnSkillActor()
{
	FTransform Trans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), AttackEffect, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), AttackEffect2, Trans);
	CastingEffectComponent->DestroyComponent();

	TArray<FOverlapResult> OutOverlaps;
	OutOverlaps = UAttackChecker::MonsterCircleCheck(OwnerMonster->GetActorLocation(),
		750.f,
		200.f,
		ECollisionChannel::ECC_GameTraceChannel6,
		Cast<AActor>(OwnerMonster));

	UAttackChecker::ApplyMonsterDamageToPlayerSectorForm(10.f, Cast<AMonster>(OwnerMonster), OutOverlaps, AttackType::STRONG, 100.f);
}

void USevarogSkill_Fourth::IndicateRange()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	SpawnParams.Instigator = OwnerMonster->GetInstigator();

	FRotator SpawnRot = OwnerMonster->GetActorRotation();
	FVector SpawnPos = OwnerMonster->GetActorLocation() - FVector(0.f, 0.f, 300.f);

	ASkillRangeActor* RangeActor = OwnerMonster->GetWorld()->SpawnActor<ASkillRangeActor>(
		SkillRangeActor,
		SpawnPos,
		SpawnRot,
		SpawnParams);

	RangeActor->SetRange(Cast<AActor>(OwnerMonster), 3, 100.f, 0.5f);
}

void USevarogSkill_Fourth::PlayParticle(AActor* OwnerActor)
{
	FTransform Trans = OwnerMonster->GetActorTransform();
	CastingEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect2, Trans);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect3, Trans);
}

void USevarogSkill_Fourth::SkillEnd()
{
	Super::SkillEnd();
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetActorHiddenInGame(false);
	Boss->GetWorldTimerManager().ClearTimer(BlinkTimer);

}

void USevarogSkill_Fourth::Teleport()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetActorRelativeLocation(Boss->GetTarget()->GetActorLocation() - Boss->GetTarget()->GetActorForwardVector() * 300);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(Boss->GetWorld(),
		BlinkEffect,
		Boss->GetActorLocation(),
		Boss->GetActorRotation());
	Boss->SetActorHiddenInGame(false);
	ActSkill();
}

void USevarogSkill_Fourth::ActSkill()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(Boss->GetActorLocation(), Boss->GetTarget()->GetActorLocation());
	Boss->SetActorRotation(Rot);

	Boss->GetAnimInst()->PlaySkillMontage(Id);
	Boss->SetExecutingSkill(this);
	PlayParticle(Cast<AActor>(OwnerMonster));
}
