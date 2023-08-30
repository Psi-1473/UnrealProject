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

void UMonsterSkill::SkillEnd()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetCastSkill(false);
	Boss->SetExecutingSkill(nullptr);
	auto AIController = Cast<ABossAIController>(Boss->GetController());
	AIController->StartAI();
	Boss->StartCooldown();
	OwnerMonster->GetWorldTimerManager().SetTimer(CoolTimeHandler, this, &UMonsterSkill::EndCoolDown, CoolTime, false);
}

void UMonsterSkill::EndCoolDown()
{
	bCanUse = true;
}

bool UMonsterSkill::IsTargetInCircleRange(AActor* HitActor, AActor* TargetActor, float RadialAngle)
{
	FVector FirstVector = HitActor->GetActorForwardVector();
	FVector SecondVector = TargetActor->GetActorLocation() - (HitActor->GetActorLocation() - HitActor->GetActorForwardVector() * 40);

	float SizeMul = FirstVector.Size() * SecondVector.Size();
	float DegreeBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(FirstVector, SecondVector) / SizeMul));
	UE_LOG(LogTemp, Warning, TEXT("Skill Angle : %f, Target To Hiter Angle : %f"), RadialAngle, DegreeBetween);
	if (DegreeBetween <= RadialAngle / 2.0f)
	{
		return true;
	}
	return false;
}
