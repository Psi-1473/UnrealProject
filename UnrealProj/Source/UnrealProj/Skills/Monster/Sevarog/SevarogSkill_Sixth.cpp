// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Sixth.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../AI/BossAIController.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

USevarogSkill_Sixth::USevarogSkill_Sixth()
{

}

void USevarogSkill_Sixth::BeginPlay()
{

}

void USevarogSkill_Sixth::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	// ĳ���� �ִϸ��̼� Ʋ��
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetSixthSkill(true);
	Boss->SetExecutingSkill(this);
	OwnerMonster->GetWorldTimerManager().SetTimer(SpawnTickTimer, this, &USevarogSkill_Sixth::SpawnTornado, 1.f, true);
}

void USevarogSkill_Sixth::PlaySkillEffect()
{

}

void USevarogSkill_Sixth::SpawnTornado()
{
	//if(n�� �̻� ��������)
	//{
	// 1. ��ȯ�� ��ü�� �� ���ֱ�
	// 
	// 2. ������ ���� ����
	//	auto pawn = TryGetPawnOwner();
	//	auto Character = Cast<ABossMonster>(pawn);
	//
	//	Character->SetCastSkill(false);
	//	Character->SetExecutingSkill(nullptr);
	//	auto AIController = Cast<ABossAIController>(Character->GetController());
	//	AIController->StartAI();
	//  ��ų ����
	//}
	// else
	//	�ƴϸ� ����̵� ��ȯ

	if (Count >= 5)
	{
		auto Boss = Cast<ABossMonster>(OwnerMonster);

		Boss->SetCastSkill(false);
		Boss->SetExecutingSkill(nullptr);
		auto AIController = Cast<ABossAIController>(Boss->GetController());
		AIController->StartAI();
		OwnerMonster->GetWorldTimerManager().ClearTimer(SpawnTickTimer);
		OwnerMonster->GetWorldTimerManager().SetTimer(SpawnTickTimer, this, &USevarogSkill_Sixth::EndSkill, 3.f, false);
	}
	else
	{
		Count++;
		// ���� ����̵� ��ü ��ȯ
		// ��ȯ�ϰ� ������ �����ؼ� ����ֱ�
	}
}

void USevarogSkill_Sixth::EndSkill()
{
	// ������ ������ ���� Destroy�ϱ�
}
