// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanAttack.h"
#include "../../AI/MonsterAIController.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	if(!(bResult && Target->GetDistanceTo(CurrrentPawn) <= 150.f))
		UE_LOG(LogTemp, Warning, TEXT("Can Attack : Return False"));

	return bResult&& Target->GetDistanceTo(CurrrentPawn) <= 150.f; //문제 ! : 이게 True를 Return 안함 거리문제였음

}
