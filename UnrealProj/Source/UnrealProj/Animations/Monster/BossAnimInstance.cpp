// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "../../Creatures/Monster/Monster.h"
#include "../../AI/MonsterAIController.h"

UBossAnimInstance::UBossAnimInstance()
{
}

void UBossAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	//DamagedMontage = LoadObject<UAnimMontage>(NULL, *GetMontageDir(TEXT("Damaged")), NULL, LOAD_None, NULL);
	AttackMontage = LoadObject<UAnimMontage>(NULL, *GetBossMontageDir(TEXT("Attack")), NULL, LOAD_None, NULL);

}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();

	if (IsValid(pawn))
	{
		Speed = FMath::Abs(pawn->GetVelocity().X);

		auto Character = Cast<AMonster>(pawn);
		bDeath = Character->bDeath;
	}
}
	
FString UBossAnimInstance::GetBossMontageDir(FString MontageType)
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

void UBossAnimInstance::AnimNotify_DamagedEnd()
{
}

void UBossAnimInstance::AnimNotify_DestroyObject()
{
}

void UBossAnimInstance::PlayDamagedMontage()
{
}

void UBossAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}
