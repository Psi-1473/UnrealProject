// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"

UStateMachine::UStateMachine()
{
	UIdleState* IdleState = NewObject<UIdleState>();
	UMoveState* MoveState = NewObject<UMoveState>();
	UJumpState* JumpState = NewObject<UJumpState>();
	UAttackState* AttackState = NewObject<UAttackState>();
	USkillState* SkillState = NewObject<USkillState>();

	IdleState->SetMachine(this);
	MoveState->SetMachine(this);
	JumpState->SetMachine(this);
	AttackState->SetMachine(this);
	SkillState->SetMachine(this);

	States.Add(STATE::IDLE, IdleState);
	States.Add(STATE::MOVE, MoveState);
	States.Add(STATE::JUMP, JumpState);
	States.Add(STATE::ATTACK, AttackState);
	States.Add(STATE::SKILL, SkillState);

	State = States[STATE::IDLE];
}

void UStateMachine::OnUpdate()
{
	if (State == nullptr)
		return;

	State->OnUpdate();
}
