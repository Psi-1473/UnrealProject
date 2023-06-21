// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerSkill_Sword_Second::UPlayerSkill_Sword_Second()
{
	Id = 2;
}

void UPlayerSkill_Sword_Second::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	auto Player = Cast<AMyPlayer>(OwnerActor);
	MoveDir = OwnerActor->GetActorForwardVector();
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	Player->bUseControllerRotationYaw = false;
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
	
}

void UPlayerSkill_Sword_Second::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);

	if (Effect == nullptr)
		return;
}
