// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterState.h"
#include "../Creatures/Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StateMachine.h"
#include "../DEFINE.h"
#include "../Skills/Skill.h"
#include "../Items/Weapons/Weapon.h"
#include "../Skills/Player/Sword/PlayerSkill_Sword_Second.h"
#include "../Inventory/EquipItemComponent.h"

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
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : IDLE"));
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
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : MOVE"));
}

void UMoveState::OnUpdate()
{
	if (Machine->GetOwner()->GetVelocity().Size() <= 0)
		Machine->SetState(STATE::IDLE);
}

void UMoveState::OnExit()
{
}
#pragma endregion

#pragma region JUMP
void UJumpState::OnEnter()
{

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : JUMP"));
}

void UJumpState::OnUpdate()
{
	if (Machine->GetOwner()->GetVelocity().Z == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Z : %f"), Machine->GetOwner()->GetVelocity().Z);
		Machine->SetState(STATE::IDLE);
	}
}

void UJumpState::OnExit()
{
}
#pragma endregion

#pragma region ATTACK

void UAttackState::OnEnter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : ATTACK"));
}

void UAttackState::OnUpdate()
{
}

void UAttackState::OnExit()
{
}
#pragma endregion

#pragma region DAMAGED
void UDamagedState::OnEnter()
{
}

void UDamagedState::OnUpdate()
{
}

void UDamagedState::OnExit()
{
}
#pragma endregion

#pragma region SKILL
void USkillState::OnEnter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : SKILL"));

}

void USkillState::OnUpdate()
{
	WEAPONTYPE WeaponType = Machine->GetOwner()->GetEquipComponent()->GetWeapon()->GetType();
	int SkillId = Machine->GetOwner()->GetSkill()->GetId();

	if (WeaponType == WEAPONTYPE::WEAPON_SWORD)
	{
		if (SkillId == 2 && Machine->GetOwner()->GetDash())
		{
			auto Skill = Cast<UPlayerSkill_Sword_Second>(Machine->GetOwner()->GetSkill());
			if (Skill == nullptr)
				return;
			Machine->GetOwner()->SetActorLocation(Machine->GetOwner()->GetActorLocation() + Machine->GetOwner()->GetActorForwardVector() * 50.f);
			//Machine->GetOwner()->AddMovementInput(Machine->GetOwner()->GetActorForwardVector(), 1.f);
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
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : SKILL CAST"));
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
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : PULLED"));
	
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

#pragma region HITANDFALL
void UHitAndFallState::OnEnter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : FALL"));
	PrevVelocity = Machine->GetOwner()->GetVelocity().Z;
}

void UHitAndFallState::OnUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("Z : %f"), Machine->GetOwner()->GetVelocity().Z);
	if (Machine->GetOwner()->GetVelocity().Z == 0 && PrevVelocity < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("KNOCKED OUT! Prev, Now : %f, %f"), PrevVelocity, Machine->GetOwner()->GetVelocity().Z);
		Machine->SetState(STATE::KNOCKED);
	}
	PrevVelocity = Machine->GetOwner()->GetVelocity().Z;
}

void UHitAndFallState::OnExit()
{
}
#pragma endregion

#pragma region KNOCKED
void UKnockedState::OnEnter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : KNOCKED"));
}

void UKnockedState::OnUpdate()
{
	
}

void UKnockedState::OnExit()
{
}
#pragma endregion

#pragma region REVIVE
void UReviveState::OnEnter()
{
	
}

void UReviveState::OnUpdate()
{
	
}

void UReviveState::OnExit()
{
}
#pragma endregion

#pragma region LOOT
void ULootState::OnEnter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("STATE : LOOT"));
	// 루팅 UI 틀기
}

void ULootState::OnUpdate()
{

}

void ULootState::OnExit()
{
}
#pragma endregion

void UDeadState::OnEnter()
{
}

void UDeadState::OnUpdate()
{
}

void UDeadState::OnExit()
{
}

void URespawnState::OnEnter()
{
	PrevTime = Machine->GetOwner()->GetWorld()->GetTimeSeconds();
}

void URespawnState::OnUpdate()
{
	float NowTime = (Machine->GetOwner()->GetWorld()->GetTimeSeconds() - PrevTime);

	UE_LOG(LogTemp, Warning, TEXT("Time  : %f, %f"), NowTime, PrevTime);
	if (NowTime >= SpawnTime)
	{
		Machine->SetState(STATE::IDLE);
	}
}

void URespawnState::OnExit()
{
}
