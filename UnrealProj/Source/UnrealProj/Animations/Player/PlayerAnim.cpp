// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Player/MyPlayerController.h"
#include "Animation/AnimMontage.h"

UPlayerAnim::UPlayerAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Player/AM_Attack.AM_Attack'"));

	if(AM.Succeeded()) AttackMontage = AM.Object;
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
			//bSprint = Character->bIsSprint;
		}
	}
}

void UPlayerAnim::PlayAttackMontage()
{
	if (!bCombo)
		return;
	if (!Montage_IsPlaying(AttackMontage))
	{
		bCombo = false;
		Montage_Play(AttackMontage, 1.f);
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
	Montage_JumpToSection(Name, AttackMontage);
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
