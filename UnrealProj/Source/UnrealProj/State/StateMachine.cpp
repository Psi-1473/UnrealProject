// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../DEFINE.h"

UStateMachine::UStateMachine()
{
	InitCharacterState();
	InitWeaponState();
}

void UStateMachine::OnUpdate()
{
	if (State != nullptr) State->OnUpdate();
	if (WeaponState != nullptr) WeaponState->OnUpdate();
}

void UStateMachine::InitCharacterState()
{
	UIdleState* IdleState = NewObject<UIdleState>();
	UMoveState* MoveState = NewObject<UMoveState>();
	UJumpState* JumpState = NewObject<UJumpState>();
	UDamagedState* DamagedState = NewObject<UDamagedState>();
	UAttackState* AttackState = NewObject<UAttackState>();
	USkillState* SkillState = NewObject<USkillState>();
	USkillCastState* SkillCastState = NewObject<USkillCastState>();
	UPulledState* PulledState = NewObject<UPulledState>();
	UKnockedState* KnockedState = NewObject<UKnockedState>();
	UHitAndFallState* HitAndFallState = NewObject<UHitAndFallState>();
	UReviveState* ReviveState = NewObject<UReviveState>();
	ULootState* LootState = NewObject<ULootState>();
	UDeadState* DeadState = NewObject<UDeadState>();
	URespawnState* RespawnState = NewObject<URespawnState>();

	IdleState->SetMachine(this);
	MoveState->SetMachine(this);
	JumpState->SetMachine(this);
	DamagedState->SetMachine(this);
	AttackState->SetMachine(this);
	SkillState->SetMachine(this);
	SkillCastState->SetMachine(this);
	PulledState->SetMachine(this);
	KnockedState->SetMachine(this);
	HitAndFallState->SetMachine(this);
	ReviveState->SetMachine(this);
	LootState->SetMachine(this);
	DeadState->SetMachine(this);
	RespawnState->SetMachine(this);

	AddState(STATE::IDLE, IdleState);
	AddState(STATE::MOVE, MoveState);
	AddState(STATE::JUMP, JumpState);
	AddState(STATE::DAMAGED, DamagedState);
	AddState(STATE::ATTACK, AttackState);
	AddState(STATE::SKILL, SkillState);
	AddState(STATE::SKILLCAST, SkillCastState);
	AddState(STATE::PULLED, PulledState);
	AddState(STATE::KNOCKED, KnockedState);
	AddState(STATE::HITANDFALL, HitAndFallState);
	AddState(STATE::REVIVE, ReviveState);
	AddState(STATE::LOOT, LootState);
	AddState(STATE::DEAD, DeadState);
	AddState(STATE::RESPAWN, RespawnState);

	State = States[STATE::IDLE];
}

void UStateMachine::InitWeaponState()
{
	USwordState* SwordState = NewObject<USwordState>();
	UBowState* BowState = NewObject<UBowState>();

	SwordState->SetMachine(this);
	BowState->SetMachine(this);

	WeaponStates.Add(WEAPONTYPE::WEAPON_SWORD, SwordState);
	WeaponStates.Add(WEAPONTYPE::WEAPON_BOW, BowState);
}

void UStateMachine::AddState(STATE StateValue, UCharacterState* StatePtr)
{
	StatePtr->SetState(StateValue);
	States.Add(StateValue, StatePtr);
}
