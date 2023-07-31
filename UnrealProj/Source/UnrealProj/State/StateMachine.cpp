// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

UStateMachine::UStateMachine()
{
	UIdleState* IdleState = NewObject<UIdleState>();
	UMoveState* MoveState = NewObject<UMoveState>();
	UJumpState* JumpState = NewObject<UJumpState>();
	UAttackState* AttackState = NewObject<UAttackState>();
	USkillState* SkillState = NewObject<USkillState>();
	USkillCastState* SkillCastState = NewObject<USkillCastState>();
	UPulledState* PulledState = NewObject<UPulledState>();
	UKnockedState* KnockedState = NewObject<UKnockedState>();

	IdleState->SetMachine(this);
	MoveState->SetMachine(this);
	JumpState->SetMachine(this);
	AttackState->SetMachine(this);
	SkillState->SetMachine(this);
	SkillCastState->SetMachine(this);
	PulledState->SetMachine(this);
	KnockedState->SetMachine(this);

	AddState(STATE::IDLE, IdleState);
	AddState(STATE::MOVE, MoveState);
	AddState(STATE::JUMP, JumpState);
	AddState(STATE::ATTACK, AttackState);
	AddState(STATE::SKILL, SkillState);
	AddState(STATE::SKILLCAST, SkillCastState);
	AddState(STATE::PULLED, PulledState);
	AddState(STATE::KNOCKED, KnockedState);

	State = States[STATE::IDLE];
}

void UStateMachine::OnUpdate()
{
	if (State == nullptr)
		return;

	State->OnUpdate();
}

void UStateMachine::AddState(STATE StateValue, UCharacterState* StatePtr)
{
	StatePtr->SetState(StateValue);
	States.Add(StateValue, StatePtr);
}
