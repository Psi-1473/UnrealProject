// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Player/MyPlayerController.h"

UPlayerAnim::UPlayerAnim()
{
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = pawn->GetVelocity().Size();

		auto Character = Cast<AMyPlayer>(pawn);

		if (Character)
		{
			auto PC = Cast<AMyPlayerController>(Character->Controller);
			//if (Speed >= 0.1)
			//	Character->SetState(MOVING);
			//
			//if (Speed <= 0 && Character->GetState() == MOVING)
			//	Character->SetState(IDLE);
			if (PC == nullptr)
				return;
			Horizontal = PC->GetHorizontal();
			Vertical = PC->GetVertical();
			//bSprint = Character->bIsSprint;
		}
	}
}
