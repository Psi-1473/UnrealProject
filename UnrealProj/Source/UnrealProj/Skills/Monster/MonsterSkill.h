// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Skill.h"
#include "MonsterSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UMonsterSkill : public USkill
{
	GENERATED_BODY()
	
public:
	bool GetCanUse() { return bCanUse; }

	void SetCanUse(bool Value) { bCanUse = Value; }

public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire
	virtual void IndicateRange() {};

	void SetOwnerMonster(TWeakObjectPtr<class AMonster> Monster) { OwnerMonster = Monster; }
	virtual void PlaySkillEffect() {};
	virtual void Attack() {};
	void EndCoolDown();

protected:
	UPROPERTY()
	TWeakObjectPtr<class AMonster> OwnerMonster;

	UPROPERTY()
	struct FTimerHandle CoolTimeHandler;

	UPROPERTY();
	float CoolTime;

	UPROPERTY()
	float RangeSize;

	UPROPERTY()
	float RangeAngle;
};
