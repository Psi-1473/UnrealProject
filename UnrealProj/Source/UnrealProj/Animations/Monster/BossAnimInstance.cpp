// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "../../Skills/Monster/MonsterSkill.h"
#include "../../AI/BossAIController.h"

UBossAnimInstance::UBossAnimInstance()
{
}

void UBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	//DamagedMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Damaged")), NULL, LOAD_None, NULL);
	AttackMontage = LoadObject<UAnimMontage>(NULL, *GetBossMontageDir(TEXT("Attack")), NULL, LOAD_None, NULL);
	SkillMontage = LoadObject<UAnimMontage>(NULL, *GetBossMontageDir(TEXT("Skill")), NULL, LOAD_None, NULL);

}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = FMath::Abs(pawn->GetVelocity().X);

		auto Character = Cast<ABossMonster>(pawn);
		bDeath = Character->bDeath;

		bCast = Character->GetCastSkill();
		if (Character->GetExecutingSkill() != nullptr)
			SkillId = Character->GetExecutingSkill()->GetId();
		if (Character->GetExecutingSkill() == nullptr)
			SkillId = 0;
	}
}
	
FString UBossAnimInstance::GetBossMontageDir(FString MontageType)
{
	auto MyPawn = Cast<AMonster>(TryGetPawnOwner());
	if (MyPawn == nullptr)
		return TEXT("");

	FString MyName = MyPawn->GetObjectName();
	FString Dir = TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Monster/Montages/");
	FString MontageName = TEXT("AM_") + MyName + TEXT("_") + MontageType;
	Dir += MyName + TEXT("/") + MontageName + TEXT(".") + MontageName + TEXT("'");

	return Dir;
}

void UBossAnimInstance::AnimNotify_DamagedEnd()
{
}

void UBossAnimInstance::AnimNotify_DestroyObject()
{
}

void UBossAnimInstance::AnimNotify_SkillEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ABossMonster>(pawn);

	Character->SetCastSkill(false);
	Character->SetExecutingSkill(nullptr);
	auto AIController = Cast<ABossAIController>(Character->GetController());
	AIController->StartAI();
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
	Character->GetExecutingSkill()->Attack();
}

void UBossAnimInstance::PlayDamagedMontage()
{
}

void UBossAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
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
