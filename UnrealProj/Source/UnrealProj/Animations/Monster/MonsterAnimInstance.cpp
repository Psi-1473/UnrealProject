// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "../../Creatures/Monster/Monster.h"
#include "../../AI/MonsterAIController.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto MyPawn = Cast<AMonster>(TryGetPawnOwner());
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
	}
}

FString UMonsterAnimInstance::GetMontageDir(FString MontageType)
{
	auto MyPawn = Cast<AMonster>(TryGetPawnOwner());
	if (MyPawn == nullptr)
		return TEXT("");

	FString MyName = MyPawn->GetObjectName();
	FString Dir = TEXT("/Script/Engine.AnimMontage'/Game/02_Blueprints/Animations/Monster/Montages/");
	FString MontageName = TEXT("AM_") + MyName + TEXT("_") + MontageType;
	Dir += MyName + TEXT("/") + MontageName + TEXT(".") + MontageName + TEXT("'");

	return Dir;
}

void UMonsterAnimInstance::AnimNotify_DamagedEnd()
{
	auto pawn = TryGetPawnOwner();
	auto Character = Cast<AMonster>(pawn);
	auto Controller = Cast<AMonsterAIController>(Character->GetController());
	Controller->StartAI();
}

void UMonsterAnimInstance::PlayDamagedMontage()
{
	if (DamagedMontage == nullptr)
		return;
	StopAllMontages(1.f);
	Montage_Play(DamagedMontage, 1.0f);
}

void UMonsterAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}
