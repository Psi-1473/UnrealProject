// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanUseSkill.h"
#include "../../AI/BossAIController.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../State/CharacterState.h"

UBTDecorator_CanUseSkill::UBTDecorator_CanUseSkill()
{
	NodeName = TEXT("CanUseSkill");
}

bool UBTDecorator_CanUseSkill::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto CurrrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrrentPawn == nullptr)
		return false;

	auto Boss = Cast<ABossMonster>(CurrrentPawn);
	if (Boss == nullptr)
		return false;
	if (Boss->GetTarget()->GetState() == Boss->GetTarget()->GetSpecificState(STATE::DEAD))
		return false;
	return bResult && Boss->GetCanSkill();
}
