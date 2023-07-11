// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Player/MyPlayerController.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Projectiles/Projectile.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Skills/Skill.h"

UPlayerAnim::UPlayerAnim()
{
	AttackMontages.Init(nullptr, (int)WEAPONTYPE::WEAPON_END);
	SkillMontages.Init(nullptr, (int)WEAPONTYPE::WEAPON_END);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack.AM_Attack'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM2(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack_Arrow.AM_Attack_Arrow'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Skill_Sword.AM_Skill_Sword'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SM2(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Skill_Arrow.AM_Skill_Arrow'"));

	if(AM.Succeeded()) AttackMontages[(int)WEAPONTYPE::WEAPON_SWORD] = AM.Object;
	if(AM2.Succeeded()) AttackMontages[(int)WEAPONTYPE::WEAPON_ARROW] = AM2.Object;
	if(SM.Succeeded()) SkillMontages[(int)WEAPONTYPE::WEAPON_SWORD] = SM.Object;
	if(SM2.Succeeded()) SkillMontages[(int)WEAPONTYPE::WEAPON_ARROW] = SM2.Object;
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = FMath::Abs(pawn->GetVelocity().X);
		JumpSpeed = pawn->GetVelocity().Z;
		
		auto Character = Cast<AMyPlayer>(pawn);

		if (Character)
		{
			auto PC = Cast<AMyPlayerController>(Character->Controller);
			if (PC == nullptr)
				return;

			Horizontal = PC->GetHorizontal();
			Vertical = PC->GetVertical();
			if (Horizontal == 1 && Vertical == 1)
			{
				Horizontal = 0.5f;
				Vertical = 0.5f;
			}

			bZoom = PC->GetIsZoom();
		}
	}
}

void UPlayerAnim::PlayAttackMontage()
{
	if (!bCombo)
		return;
	if (!Montage_IsPlaying(AttackMontages[(int)WeaponType]))
	{
		bCombo = false;
		Montage_Play(AttackMontages[(int)WeaponType], 1.f);
		if (WeaponType == WEAPONTYPE::WEAPON_ARROW)
		{
			FName Name;
			Name = (bZoom) ? FName(*FString::Printf(TEXT("HeavyAttack"))) : FName(*FString::Printf(TEXT("Attack")));
			Montage_JumpToSection(Name, AttackMontages[(int)WeaponType]);
			return;
		}
		JumpToSection(AttackMontages[(int)WeaponType], AttackStep);
		AttackStep++;
	}
}
void UPlayerAnim::PlaySkillMontage(int32 SkillNumber)
{
	if (!Montage_IsPlaying(SkillMontages[(int)WeaponType]))
	{
		Montage_Play(SkillMontages[(int)WeaponType], 1.f);
		JumpToSection(SkillMontages[(int)WeaponType], SkillNumber);
	}
}
FName UPlayerAnim::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UPlayerAnim::JumpToSection(UAnimMontage* Montage, int32 SectionIndex)
{
	//FName Name = GetAttackMontageName(SectionIndex);
	FName Name = FName(*FString::FromInt(SectionIndex));
	Montage_JumpToSection(Name, Montage);
}

void UPlayerAnim::AnimNotify_Combo()
{
	bCombo = true;
}

void UPlayerAnim::AnimNotify_FireArrow()
{
	auto pawn = TryGetPawnOwner();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(pawn);

	Cast<AMyPlayerController>(MyPlayer->GetController())->Fire();
}

void UPlayerAnim::AnimNotify_SkillEffect()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);

	USkill* Skill = Character->GetSkill();
	Skill->PlayParticle(Character);

}

void UPlayerAnim::AnimNotify_SkillEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	Character->SetState(STATE::IDLE);
	Character->SetSkill(nullptr);
	bCombo = true;
	AttackStep = 1;
	if (Montage_IsPlaying(SkillMontages[(int)WeaponType]))
		StopAllMontages(1.f);
}

void UPlayerAnim::AnimNotify_DashStart()
{
	auto pawn = TryGetPawnOwner();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(pawn);
	MyPlayer->SetDash(true);
	USkill* Skill = MyPlayer->GetSkill();
	Skill->PlayParticle(MyPlayer);
	
}
void UPlayerAnim::AnimNotify_DashEnd()
{
	auto pawn = TryGetPawnOwner();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(pawn);
	MyPlayer->SetDash(false);
	MyPlayer->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	USkill* Skill = MyPlayer->GetSkill();
	Skill->DestroyActor();
}
void UPlayerAnim::AnimNotify_HitCheck()
{
	auto pawn = TryGetPawnOwner();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(pawn);

	MyPlayer->AttackCheck(100.f, 150.f, 150.f);
}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	
	Character->SetState(STATE::IDLE);
	bCombo = true;
	AttackStep = 1;
	if (Montage_IsPlaying(AttackMontages[(int)WeaponType]))
		StopAllMontages(1.f);
	
}
