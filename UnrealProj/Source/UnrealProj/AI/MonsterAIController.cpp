// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"


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
			// TODO
		}
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
