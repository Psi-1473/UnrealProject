// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanUseSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UBTDecorator_CanUseSkill : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CanUseSkill();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
