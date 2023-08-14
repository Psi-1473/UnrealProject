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
	// 캐스팅 애니메이션 틀기
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
	//if(n초 이상 지났으면)
	//{
	// 1. 소환된 객체들 다 없애기
	// 
	// 2. 보스몹 상태 설정
	//	auto pawn = TryGetPawnOwner();
	//	auto Character = Cast<ABossMonster>(pawn);
	//
	//	Character->SetCastSkill(false);
	//	Character->SetExecutingSkill(nullptr);
	//	auto AIController = Cast<ABossAIController>(Character->GetController());
	//	AIController->StartAI();
	//  스킬 종료
	//}
	// else
	//	아니면 토네이도 소환

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
		// 저거 토네이도 객체 소환
		// 소환하고 변수에 저장해서 들고있기
	}
}

void USevarogSkill_Sixth::EndSkill()
{
	// 저장한 변수들 전부 Destroy하기
}
