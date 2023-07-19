// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_UseRandomSkill.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../../AI/MonsterAIController.h"
#include "../../Creatures/Monster/BossMonster.h"

UBTTask_UseRandomSkill::UBTTask_UseRandomSkill()
{
}

EBTNodeResult::Type UBTTask_UseRandomSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	auto CurrentMonster = Cast<ABossMonster>(CurrentPawn);
	if (CurrentMonster == nullptr)
		return EBTNodeResult::Failed;
	
	CurrentMonster->UseSkill();

	return EBTNodeResult::Type();
}
