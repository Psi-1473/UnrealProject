// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Player/MyPlayerController.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Projectiles/Projectile.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Skills/Skill.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "../../State/CharacterState.h"
#include "../../State/WeaponState.h"
#include "../../Items/Weapons/Bow.h"

UPlayerAnim::UPlayerAnim()
{
	AttackMontages.Init(nullptr, (int)WEAPONTYPE::WEAPON_END);
	SkillMontages.Init(nullptr, (int)WEAPONTYPE::WEAPON_END);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack.AM_Attack'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM2(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack_Arrow.AM_Attack_Arrow'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Skill_Sword.AM_Skill_Sword'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SM2(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Skill_Arrow.AM_Skill_Arrow'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Damaged.AM_Damaged'"));

	if(AM.Succeeded()) AttackMontages[(int)WEAPONTYPE::WEAPON_SWORD] = AM.Object;
	if(AM2.Succeeded()) AttackMontages[(int)WEAPONTYPE::WEAPON_ARROW] = AM2.Object;
	if(SM.Succeeded()) SkillMontages[(int)WEAPONTYPE::WEAPON_SWORD] = SM.Object;
	if(SM2.Succeeded()) SkillMontages[(int)WEAPONTYPE::WEAPON_ARROW] = SM2.Object;
	if(DM.Succeeded()) DamagedMontage = DM.Object;
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		JumpSpeed = pawn->GetVelocity().Z;

		auto Character = Cast<AMyPlayer>(pawn);
		if (Character)
		{
			if(Character->GetState() != nullptr)
				CharacterState = Character->GetState()->GetState();

			auto Arrow = Cast<UBowState>(Character->GetWeaponState());
			if(Arrow) bZoom = Arrow->GetZoom();

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
void UPlayerAnim::PlayDamagedMontage()
{
	Montage_Play(DamagedMontage);
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

	//Cast<AMyPlayerController>(MyPlayer->GetController())->Fire();
	auto BowState = Cast<UBowState>(MyPlayer->GetWeaponState());
	if(BowState) BowState->Fire();
}

void UPlayerAnim::AnimNotify_SkillEffect()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);

	UPlayerSkill* Skill = Character->GetSkill();
	Skill->PlayParticle(Character);

}

void UPlayerAnim::AnimNotify_SkillEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	Character->GetSkill()->SkillEnd();
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
	UPlayerSkill* Skill = MyPlayer->GetSkill();
	Skill->PlayParticle(MyPlayer);
	
}
void UPlayerAnim::AnimNotify_DashEnd()
{
	auto pawn = TryGetPawnOwner();
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(pawn);
	MyPlayer->SetDash(false);
	MyPlayer->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	UPlayerSkill* Skill = MyPlayer->GetSkill();
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
	SetComboAndStepZero();
	if (Montage_IsPlaying(AttackMontages[(int)WeaponType]))
		StopAllMontages(1.f);
	
}

void UPlayerAnim::AnimNotify_SetIdle()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	if (Character)
		Character->SetState(STATE::IDLE);
}

void UPlayerAnim::AnimNotify_SetRevive()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	if (Character)
		Character->SetState(STATE::REVIVE);
}

void UPlayerAnim::SetComboAndStepZero()
{
	bCombo = true;
	AttackStep = 1;
}
