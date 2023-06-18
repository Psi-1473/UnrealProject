// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"

void UPlayerSkill_Sword_First::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	UE_LOG(LogTemp, Warning, TEXT("SWORD FIRST SKILL"));

	auto OwnerPlayer = Cast<AMyPlayer>(OwnerActor);
	if (OwnerPlayer == nullptr)
		return;

	OwnerPlayer->GetAnimInst()->PlaySkillMontage(RegisteredKey);
}
