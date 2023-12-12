// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "../../State/CharacterState.h"

void ABow::OnLeftMouseClicked(AMyPlayer* Player)
{
	Super::OnLeftMouseClicked(Player);
}

void ABow::OnRightMouseClicked(AMyPlayer* Player)
{
	Super::OnRightMouseClicked(Player);

	if (Player->GetState() == Player->GetSpecificState(STATE::ATTACK) && CameraMoved == false)
		return;

	ZoomIn(Player);
}

void ABow::OnRightMouseReleased(AMyPlayer* Player)
{
	Super::OnRightMouseReleased(Player);

	if (Player->GetState() == Player->GetSpecificState(STATE::ATTACK) && CameraMoved == false)
		return;
	ZoomOut(Player);
}

void ABow::ZoomIn(AMyPlayer* Player)
{
	if (Player->GetState() != Player->GetSpecificState(STATE::IDLE) &&
		Player->GetState() != Player->GetSpecificState(STATE::MOVE) &&
		Player->GetState() != Player->GetSpecificState(STATE::JUMP))
		return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, 60.f, 0.f));
	Player->GetCamera()->FieldOfView = 75.f;
	Movement->MaxWalkSpeed = 350.f;
	CameraMoved = true;
	bZoom = true;
}

void ABow::ZoomOut(AMyPlayer* Player)
{
	if (CameraMoved == false) return;
	auto Movement = Cast<UCharacterMovementComponent>(Player->GetMovementComponent());
	Player->GetCamera()->SetRelativeLocation(Player->GetCamera()->GetRelativeLocation() + FVector(0.f, -60.f, 0.f));
	Player->GetCamera()->FieldOfView = 90.f;
	Movement->MaxWalkSpeed = 600.f;
	CameraMoved = false;
	bZoom = false;
}
