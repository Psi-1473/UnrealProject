// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ABossAIController::ABossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/07_AI/Monster/Boss/BB_Boss.BB_Boss'"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/07_AI/Monster/Boss/BT_Boss.BT_Boss'"));
	
	if (BD.Succeeded()) BlackBoardData = BD.Object;
	if (BT.Succeeded()) BehaviorTree = BT.Object;

}

void ABossAIController::OnPossess(APawn* InPawn)
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

void ABossAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
