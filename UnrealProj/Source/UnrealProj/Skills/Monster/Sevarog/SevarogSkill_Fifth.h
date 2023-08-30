// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Fifth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Fifth : public UMonsterSkill
{
	GENERATED_BODY()
	
public:
	USevarogSkill_Fifth();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override; // 스킬 시작
	virtual void AttackOrSpawnSkillActor() override; // Hit체크, 스킬 액터 소환

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;
};
