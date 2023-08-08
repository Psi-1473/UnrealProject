// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkill.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "../../AI/BossAIController.h"

void UMonsterSkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (OwnerMonster == nullptr)
		return;

	auto Boss = Cast<ABossMonster>(OwnerMonster);

	if (Boss == nullptr)
		return;
	// AI ¿·±Ò ∏ÿ√·¥Ÿ.
	auto AIController = Cast<ABossAIController>(Boss->GetController());
	AIController->StopAI();

	UE_LOG(LogTemp, Warning, TEXT("STOP AI FOR SKILL"));
}

void UMonsterSkill::EndCoolDown()
{
	bCanUse = true;
}
