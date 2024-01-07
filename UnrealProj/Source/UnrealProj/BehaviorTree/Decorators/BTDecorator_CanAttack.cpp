// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "../../AI/MonsterAIController.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Creatures/Monster/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../State/CharacterState.h"
#include "../../State/StateMachine.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto CurrrentPawn = Cast<AActor>(OwnerComp.GetAIOwner()->GetPawn());
	if (CurrrentPawn == nullptr)
		return false;

	auto Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (Target == nullptr)
		return false;

	if (Target->GetStateMachine()->GetState()->GetState() == STATE::DEAD)
		return false;

	auto Boss = Cast<ABossMonster>(CurrrentPawn);
	UE_LOG(LogTemp, Warning, TEXT("Distance : %f"), Target->GetDistanceTo(CurrrentPawn));
	if(Boss == nullptr)
		return bResult && Target->GetDistanceTo(CurrrentPawn) <= 150.f;
	else
		return bResult && Target->GetDistanceTo(CurrrentPawn) <= 600.f;
}
