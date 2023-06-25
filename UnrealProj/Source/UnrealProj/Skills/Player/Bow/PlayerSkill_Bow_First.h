// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Skill.h"
#include "PlayerSkill_Bow_First.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill_Bow_First : public USkill
{
	GENERATED_BODY()
public:
	UPlayerSkill_Bow_First();

public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;
	virtual void DestroyActor() override;
	virtual void CastToExecute(AActor* OwnerActor) override;
private:
	UPROPERTY()
	class ASkillRangeActor* RangeActor;
};
