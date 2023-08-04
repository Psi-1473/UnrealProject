// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Second.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"

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
	Boss->SetExecutingSkill(this);
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
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	TargetPos = Boss->GetTarget()->GetActorLocation();
	FTransform Trans(TargetPos);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerMonster->GetWorld(), FireEffect, Trans);

	OwnerMonster->GetWorldTimerManager().SetTimer(HitCheckTimerHandle, this, &USevarogSkill_Second::HitCheck, 0.5f, false);
}

void USevarogSkill_Second::HitCheck()
{
	float AttackX = 100.f;
	float AttackY = 100.f;
	float AttackZ = 100.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Cast<AActor>(OwnerMonster));
	FVector BoxVector(AttackX, AttackY, AttackZ);
	FVector SkillLocation = TargetPos;
	bool bResult = OwnerMonster->GetWorld()->SweepMultiByChannel(
		OUT HitResults,
		SkillLocation,
		SkillLocation + OwnerMonster->GetActorForwardVector() * AttackX,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeBox(BoxVector),
		Params);
	// Attack 콜리전 새로 제대로 만들 것

	FVector Vec = OwnerMonster->GetActorForwardVector() * AttackX;
	FVector Center = SkillLocation + Vec * 0.5f;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;

	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugBox(OwnerMonster->GetWorld(), Center, BoxVector, Rotation, DrawColor, false, 2.f);
	if (bResult)
	{
		for (FHitResult HitResult : HitResults)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			AMyPlayer* Player = Cast<AMyPlayer>(HitResult.GetActor());
			FDamageEvent DamageEvent;
			if (Player == nullptr)
				return;
			Player->OnDamaged(10.f, DamageEvent, OwnerMonster->GetController(), Cast<AActor>(OwnerMonster), AttackType::DOWN); //Temp
		}
	}

	OwnerMonster->GetWorldTimerManager().ClearTimer(HitCheckTimerHandle);
}
