// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Player/MyPlayerController.h"

#include "Animation/AnimMontage.h"

UPlayerAnim::UPlayerAnim()
{
	AttackMontages.Init(nullptr, WEAPON_END);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack.AM_Attack'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM2(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/Montages/AM_Attack_Arrow.AM_Attack_Arrow'"));

	if(AM.Succeeded()) AttackMontages[WEAPON_SWORD] = AM.Object;
	if(AM2.Succeeded()) AttackMontages[WEAPON_ARROW] = AM2.Object;
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
			bZoom = PC->GetIsZoom();
		}
	}
}

void UPlayerAnim::PlayAttackMontage()
{
	if (!bCombo)
		return;
	if (!Montage_IsPlaying(AttackMontages[WeaponType]))
	{
		bCombo = false;
		Montage_Play(AttackMontages[WeaponType], 1.f);

		if (WeaponType == WEAPON_ARROW)
			return;

		JumpToSection(AttackStep);
		AttackStep++;
	}
}
FName UPlayerAnim::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UPlayerAnim::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontages[WeaponType]);
}

void UPlayerAnim::AnimNotify_Combo()
{
	bCombo = true;
}

void UPlayerAnim::AnimNotify_AttackEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMyPlayer>(pawn);
	Character->SetState(STATE::IDLE);
	bCombo = true;
	AttackStep = 1;
}
