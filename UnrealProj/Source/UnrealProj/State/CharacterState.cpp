// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterState.h"
#include "../Creatures/Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachine.h"
#include "../Skills/Skill.h"
#include "../Items/Weapons/Weapon.h"
#include "../Skills/Player/Sword/PlayerSkill_Sword_Second.h"

void UCharacterState::OnEnter()
{
}

void UCharacterState::OnUpdate()
{
}

void UCharacterState::OnExit()
{
}

#pragma region IDLE
void UIdleState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : IDLE"));
}

void UIdleState::OnUpdate()
{
}

void UIdleState::OnExit()
{
}
#pragma endregion

#pragma region MOVE
void UMoveState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : MOVE"));
}

void UMoveState::OnUpdate()
{
	if (Machine->GetOwner()->GetVelocity().Size() <= 0)
		Machine->GetOwner()->SetState(STATE::IDLE);
}

void UMoveState::OnExit()
{
}
#pragma endregion

#pragma region JUMP
void UJumpState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : JUMP"));
}

void UJumpState::OnUpdate()
{
}

void UJumpState::OnExit()
{
}
#pragma endregion

#pragma region ATTACK

void UAttackState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : ATTACK"));
}

void UAttackState::OnUpdate()
{
}

void UAttackState::OnExit()
{
}
#pragma endregion

#pragma region SKILL
void USkillState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : SKILL"));

}

void USkillState::OnUpdate()
{
	WEAPONTYPE WeaponType = Machine->GetOwner()->GetWeapon()->GetType();
	int SkillId = Machine->GetOwner()->GetSkill()->GetId();

	if (WeaponType == WEAPONTYPE::WEAPON_SWORD)
	{
		if (SkillId == 2 && Machine->GetOwner()->GetDash())
		{
			auto Skill = Cast<UPlayerSkill_Sword_Second>(Machine->GetOwner()->GetSkill());
			if (Skill == nullptr)
				return;
			Machine->GetOwner()->AddMovementInput(Skill->GetMoveDir());
		}
	}
}

void USkillState::OnExit()
{
	Machine->GetOwner()->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Machine->GetOwner()->bUseControllerRotationYaw = true;
}
#pragma endregion 

#pragma region SKILLCast
void USkillCastState::OnEnter()
{
}

void USkillCastState::OnUpdate()
{
}

void USkillCastState::OnExit()
{
}
#pragma endregion

#pragma region PULLED
void UPulledState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : PULLED"));
}

void UPulledState::OnUpdate()
{
	// 타겟 포지션으로 이동시킨다.
	//Machine->GetOwner()->AddMovementInput(Machine->GetOwner()->GetPullPos());
	//Machine->GetOwner()->SetActorLocation(Machine->GetOwner()->GetPullPos());
}

void UPulledState::OnExit()
{
	//Machine->GetOwner()->SetState(STATE::IDLE); // 임시로 Idle
}
#pragma endregion

#pragma region KNOCKED
void UKnockedState::OnEnter()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : KNOCKED"));
	Machine->GetOwner()->SetKnocked(true);
}

void UKnockedState::OnUpdate()
{
	if (FMath::Abs(Machine->GetOwner()->GetVelocity().Z) <= 0.1f)
	{
		Machine->GetOwner()->SetState(STATE::IDLE);
		Machine->GetOwner()->SetKnocked(false);
	}
}

void UKnockedState::OnExit()
{
}
#pragma endregion