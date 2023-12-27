// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "../../Creatures/Monster/Monster.h"
#include "../../Creatures/Monster/SpawnMonster.h"
#include "../../AI/MonsterAIController.h"



UMonsterAnimInstance::UMonsterAnimInstance()
{
	
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	DamagedMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Damaged")), NULL, LOAD_None, NULL);
	AttackMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Attack")), NULL, LOAD_None, NULL);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = FMath::Abs(pawn->GetVelocity().X);

		auto Character = Cast<AMonster>(pawn);	
		bDeath = Character->GetDeath();
	}
}


void UMonsterAnimInstance::AnimNotify_HitCheck()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<ASpawnMonster>(pawn);

	Character->AttackCheck();
}

void UMonsterAnimInstance::AnimNotify_DamagedEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMonster>(pawn);
	auto Controller = Cast<AMonsterAIController>(Character->GetController());
	Controller->StartAI();
}

void UMonsterAnimInstance::AnimNotify_DestroyObject()
{
	OnDied.Broadcast();
}

