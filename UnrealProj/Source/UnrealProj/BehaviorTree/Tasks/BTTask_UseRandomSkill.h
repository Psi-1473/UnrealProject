// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_UseRandomSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UBTTask_UseRandomSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_UseRandomSkill();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
