// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Second.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../EffectActor/SkillRangeActor.h"
#include "Sound/SoundWave.h"
#include "../../../Helpers/AttackChecker.h"


USevarogSkill_Second::USevarogSkill_Second()
{
	Id = 2;
	CoolTime = 10.f;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Subjugate/FX/P_Sub_Cast.P_Sub_Cast'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CAST2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_SoulStageEmbers.P_SoulStageEmbers'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Subjugate/FX/P_SubjugateSwirls.P_SubjugateSwirls'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> HSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/Sevarog/Sound_Sevarog_Skill2Shot.Sound_Sevarog_Skill2Shot'"));

	if (CAST.Succeeded()) CastEffect = CAST.Object;
	if (CAST2.Succeeded()) CastEffect2 = CAST2.Object;
	if (FIRE.Succeeded()) FireEffect = FIRE.Object;
	if (HSound.Succeeded()) HitSound = HSound.Object;
}

void USevarogSkill_Second::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	TargetPos = Boss->GetTarget()->GetActorLocation();
	Boss->SetExecutingSkill(this);
	PlayParticle(Cast<AActor>(OwnerMonster));
}

void USevarogSkill_Second::IndicateRange()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	SpawnParams.Instigator = OwnerMonster->GetInstigator();

	FRotator SpawnRot = OwnerMonster->GetActorRotation();
	FVector SpawnPos = TargetPos;

	ASkillRangeActor* RangeActor = OwnerMonster->GetWorld()->SpawnActor<ASkillRangeActor>(
		SkillRangeActor,
		SpawnPos,
		SpawnRot,
		SpawnParams);

	RangeActor->SetRange(Cast<AActor>(OwnerMonster), 1, 360.f, 0.5f);
}

void USevarogSkill_Second::AttackOrSpawnSkillActor()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	//TargetPos = Boss->GetTarget()->GetActorLocation();
	FTransform Trans(TargetPos);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), FireEffect, Trans);

	OwnerMonster->GetWorldTimerManager().SetTimer(HitCheckTimerHandle, this, &USevarogSkill_Second::HitCheck, 0.5f, false);
}

void USevarogSkill_Second::PlayParticle(AActor* OwnerActor)
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(true);
	Boss->SetExecutingSkill(this);
	FTransform Trans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect, Trans);
	FTransform TargetTrans = OwnerMonster->GetActorTransform();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), CastEffect2, TargetTrans);
}

void USevarogSkill_Second::HitCheck()
{
	TArray<FHitResult> HitResults;
	FVector SkillLocation = TargetPos;

	HitResults = UAttackChecker::MonsterCubeCheck(FVector(100.f, 100.f, 100.f), SkillLocation, ECollisionChannel::ECC_GameTraceChannel6, Cast<AActor>(OwnerMonster));
	UAttackChecker::ApplyHitDamageToActors(10.f, Cast<AActor>(OwnerMonster), HitResults, AttackType::DOWN);

	//FVector BoxVector(AttackX, AttackY, AttackZ);
	//
	//bool bResult = OwnerMonster->GetWorld()->SweepMultiByChannel(
	//	OUT HitResults,
	//	SkillLocation,
	//	SkillLocation + OwnerMonster->GetActorForwardVector() * AttackX,
	//	FQuat::Identity,
	//	ECollisionChannel::ECC_GameTraceChannel6,
	//	FCollisionShape::MakeBox(BoxVector),
	//	Params);
	//// Attack 콜리전 새로 제대로 만들 것
	//
	//FVector Vec = OwnerMonster->GetActorForwardVector() * AttackX;
	//FVector Center = SkillLocation + Vec * 0.5f;
	//FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	//FColor DrawColor;
	//
	//if (bResult)
	//	DrawColor = FColor::Green;
	//else
	//	DrawColor = FColor::Red;
	//
	//DrawDebugBox(OwnerMonster->GetWorld(), Center, BoxVector, Rotation, DrawColor, false, 2.f);
	//if (bResult)
	//{
	//	for (FHitResult HitResult : HitResults)
	//	{
	//		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
	//		AMyPlayer* Player = Cast<AMyPlayer>(HitResult.GetActor());
	//		FDamageEvent DamageEvent;
	//		if (Player == nullptr || OwnerMonster == nullptr)
	//			return;
	//
	//		if (OwnerMonster->GetDeath() == true)
	//			return;
	//		Player->OnDamaged(10.f, DamageEvent, OwnerMonster->GetController(), Cast<AActor>(OwnerMonster), AttackType::DOWN); //Temp
	//	}
	//}
	PlaySoundAtLocation(OwnerMonster->GetWorld(), TargetPos, HitSound);
	OwnerMonster->GetWorldTimerManager().ClearTimer(HitCheckTimerHandle);
}
