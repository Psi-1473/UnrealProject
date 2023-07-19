// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanDash.h"
#include "../../AI/BossAIController.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanDash::UBTDecorator_CanDash()
{
	NodeName = TEXT("CanDash");
}

bool UBTDecorator_CanDash::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto CurrrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrrentPawn == nullptr)
		return false;

	auto Boss = Cast<ABossMonster>(CurrrentPawn);
	if (Boss == nullptr)
		return false;

	auto Target = Boss->GetTarget();

	if (Target == nullptr)
		return false;
	

	return bResult && Target->GetDistanceTo(CurrrentPawn) > 1000.f;
}
