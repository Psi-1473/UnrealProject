// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "../../Creatures/Monster/Monster.h"

FString UEnemyAnimInstance::GetMontageDir(FString MontageType)
{
	auto MyPawn = Cast<AMonster>(TryGetPawnOwner());
	if (MyPawn == nullptr)
		return TEXT("");

	FString MyName = FString::FromInt(MyPawn->GetObjectId());
	FString Dir = TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Monster/Montages/");
	FString MontageName = TEXT("AM_") + MyName + TEXT("_") + MontageType;
	Dir += MyName + TEXT("/") + MontageName + TEXT(".") + MontageName + TEXT("'");

	return Dir;
}

void UEnemyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}

void UEnemyAnimInstance::PlayDamagedMontage()
{
	if (DamagedMontage == nullptr)
		return;
	StopAllMontages(1.f);
	Montage_Play(DamagedMontage, 1.0f);
}
