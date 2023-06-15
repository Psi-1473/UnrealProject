// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../../Creatures/Monster/Monster.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../AI/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("AttackTarget");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	auto CurrentMonster = Cast<AMonster>(CurrentPawn);
	auto TargetPlayer = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	CurrentMonster->AttackTarget(TargetPlayer);

	return EBTNodeResult::Type();
}
