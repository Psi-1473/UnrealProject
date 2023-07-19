// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../../AI/MonsterAIController.h"
#include "../../Creatures/Monster/Monster.h"
#include "../../Creatures/Monster/SpawnMonster.h"
#include "../../Spawner/MonsterSpawner.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = (TEXT("FindPatrolPosition"));
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto CurrentPawn = OwnerComp.GetAIOwner();
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	auto Mob = Cast<ASpawnMonster>(CurrentPawn->GetPawn());
	if (Mob == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mob NULL"));
		return EBTNodeResult::Failed;
	}

	FVector CenterPos = Mob->GetSpawner()->GetActorLocation();


	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(CenterPos, 500.f, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("PatrolPos"), RandomLocation.Location);
	}
	return EBTNodeResult::Type();
}
