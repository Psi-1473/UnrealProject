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
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire

	void SetOwnerMonster(TWeakObjectPtr<class AMonster> Monster) { OwnerMonster = Monster; }
	virtual void PlaySkillEffect() {};
	virtual void Attack() {};
protected:
	UPROPERTY();
	TWeakObjectPtr<class AMonster> OwnerMonster;
};
