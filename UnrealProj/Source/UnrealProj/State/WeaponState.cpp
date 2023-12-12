// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponState.h"
#include "StateMachine.h"
#include "CharacterState.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Skills/Player/PlayerSkill.h"
#include "../Animations/Player/PlayerAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

void UWeaponState::OnLeftMouseClicked(AMyPlayer* Player)
{
	if (Machine->GetState() != Machine->GetState(STATE::IDLE) &&
		Machine->GetState() != Machine->GetState(STATE::MOVE) &&
		Machine->GetState() != Machine->GetState(STATE::JUMP) &&
		Machine->GetState() != Machine->GetState(STATE::ATTACK) &&
		Machine->GetState() != Machine->GetState(STATE::SKILLCAST))
		return;

	if (Machine->GetState() == Machine->GetState(STATE::SKILL))
		return;

	if (Machine->GetState() == Machine->GetState(STATE::SKILLCAST))
		Player->GetSkill()->CastToExecute(Player);
	else
	{
		if (Player->GetState() != Player->GetSpecificState(STATE::ATTACK))
			Player->SetState(STATE::ATTACK);

		Player->GetAnimInst()->PlayAttackMontage();
	}
}


#pragma region SwordState
void USwordState::OnLeftMouseClicked(AMyPlayer* Player)
{
	UWeaponState::OnLeftMouseClicked(Player);
}

void USwordState::OnRightMouseClicked(AMyPlayer* Player)
{
}

void USwordState::OnRightMouseReleased(AMyPlayer* Player)
{
}

void USwordState::OnUpdate()
{
}

#pragma endregion


#pragma region BowState
void UBowState::OnLeftMouseClicked(AMyPlayer* Player)
{
	UWeaponState::OnLeftMouseClicked(Player);
}

void UBowState::OnRightMouseClicked(AMyPlayer* Player)
{
	if (Machine->GetState() == Machine->GetState(STATE::ATTACK) && CameraMoved == false)
		return;

	ZoomIn(Player);
}

void UBowState::OnRightMouseReleased(AMyPlayer* Player)
{
	if (Machine->GetState() == Machine->GetState(STATE::ATTACK) && CameraMoved == false)
		return;
	ZoomOut(Player);
}

void UBowState::OnUpdate()
{
}


void UBowState::ZoomIn(AMyPlayer* Player)
{
	if (Machine->GetState() != Machine->GetState(STATE::IDLE) &&
		Machine->GetState() != Machine->GetState(STATE::MOVE) &&
		Machine->GetState() != Machine->GetState(STATE::JUMP))
		return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, 60.f, 0.f));
	Player->GetCamera()->FieldOfView = 75.f;
	Movement->MaxWalkSpeed = 350.f;
	CameraMoved = true;
	bZoom = true;
}

void UBowState::ZoomOut(AMyPlayer* Player)
{
	if (CameraMoved == false) return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, -60.f, 0.f));
	Player->GetCamera()->FieldOfView = 90.f;
	Movement->MaxWalkSpeed = 600.f;
	CameraMoved = false;
	bZoom = false;
}
#pragma endregion


