// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "../../Skills/Monster/MonsterSkill.h"
#include "../../AI/BossAIController.h"
#include "../../Stat/MonsterStatComponent.h"

UBossAnimInstance::UBossAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> START(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Monster/Montages/5/AM_5_Start.AM_5_Start'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DIE(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Monster/Montages/5/AM_5_Die.AM_5_Die'"));
	if (START.Succeeded()) StartMontage = START.Object;
	if (DIE.Succeeded()) DieMontage = DIE.Object;
}

void UBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	//DamagedMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Damaged")), NULL, LOAD_None, NULL);
	AttackMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Attack")), NULL, LOAD_None, NULL);
	SkillMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Skill")), NULL, LOAD_None, NULL);
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = FMath::Abs(pawn->GetVelocity().X);

		auto Character = Cast<ABossMonster>(pawn);
		bDeath = Character->GetDeath();

		bCast = Character->GetCastSkill();
		bSixthSkill = Character->GetSixthSkill();

		if (Character->GetExecutingSkill() != nullptr)
			SkillId = Character->GetExecutingSkill()->GetId();
		if (Character->GetExecutingSkill() == nullptr)
			SkillId = 0;
	}
}


void UBossAnimInstance::AnimNotify_DamagedEnd()
{
}

void UBossAnimInstance::AnimNotify_DestroyObject()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	Character->DestroyObject();
}

void UBossAnimInstance::AnimNotify_SkillEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	Character->GetExecutingSkill()->SkillEnd();
}

void UBossAnimInstance::AnimNotify_PlayEffect()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	Character->GetExecutingSkill()->PlaySkillEffect();
}

void UBossAnimInstance::AnimNotify_HitCheck()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	Character->GetExecutingSkill()->AttackOrSpawnSkillActor();
}

void UBossAnimInstance::AnimNotify_IndicateRange()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	if (Character->GetExecutingSkill() == nullptr)
		return;

	Character->GetExecutingSkill()->IndicateRange();
}

void UBossAnimInstance::AnimNotify_DashEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	bDash = false;
	Character->SetDashEffectVisibility(false);
}
void UBossAnimInstance::PlayStartMontage()
{
	if (!Montage_IsPlaying(StartMontage))
	{
		Montage_Play(StartMontage, 1.0f);
	}
}

void UBossAnimInstance::PlayDieMontage()
{
	if (!Montage_IsPlaying(DieMontage))
	{
		StopAllMontages(1.f);
		Montage_Play(DieMontage, 1.0f);
	}
	// 죽는 애니메이션 재생
	// Notify에 사망 등록
}

void UBossAnimInstance::PlaySkillMontage(int32 Id)
{
	if (!Montage_IsPlaying(SkillMontage))
	{
		Montage_Play(SkillMontage, 1.0f);
		JumpToSection(SkillMontage, Id);
	}
}

void UBossAnimInstance::JumpToSection(UAnimMontage* Montage, int32 Section)
{
	FName Name = FName(*FString::FromInt(Section));
	Montage_JumpToSection(Name, Montage);
}
