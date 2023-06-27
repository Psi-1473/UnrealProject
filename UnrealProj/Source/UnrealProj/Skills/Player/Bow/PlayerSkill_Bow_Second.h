// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Skill.h"
#include "PlayerSkill_Bow_Second.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill_Bow_Second : public USkill
{
	GENERATED_BODY()
public:
	UPlayerSkill_Bow_Second();

public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;

private:
	class UParticleSystem* PlayerParticle;
};
