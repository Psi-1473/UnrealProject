// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BrainComponent.h"


AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/07_AI/Monster/BB_Monster.BB_Monster'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/07_AI/Monster/BT_Monster.BT_Monster'"));

	if (BD.Succeeded()) BlackBoardData = BD.Object;
	if (BT.Succeeded()) BehaviorTree = BT.Object;

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BlackBoardData, BlackboardComp)) // 매개변수 : 블랙보드 데이터, 컴포넌트
	{
		if (RunBehaviorTree(BehaviorTree))//매개변수 : Behavior Tree
		{

		}
	}
	
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMonsterAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (nullptr != BehaviorTreeComponent)
		BehaviorTreeComponent->StopTree();
}

void AMonsterAIController::StartAI()
{
	UE_LOG(LogTemp, Warning, TEXT("START"));
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BehaviorTreeComponent == nullptr)
		return;
	
	BehaviorTreeComponent->StartTree(*BehaviorTree, EBTExecutionMode::Looped);
}
