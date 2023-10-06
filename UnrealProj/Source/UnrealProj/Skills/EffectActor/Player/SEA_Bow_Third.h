// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffectActor.h"
#include "SEA_Bow_Third.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASEA_Bow_Third : public ASkillEffectActor
{
	GENERATED_BODY()
	
public:
	ASEA_Bow_Third();

	virtual void BeginPlay() override;
	void AttackCheck();

private:
	int AttackCount = 0;

	UPROPERTY()
	FTimerHandle AttackDelayTimerHandle;
};
