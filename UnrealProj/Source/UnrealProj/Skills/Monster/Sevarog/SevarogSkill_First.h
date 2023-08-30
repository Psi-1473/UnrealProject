// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_First.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_First : public UMonsterSkill
{
	GENERATED_BODY()
	
public:
	USevarogSkill_First();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void AttackOrSpawnSkillActor() override;
	virtual void IndicateRange() override;

	
private:
	void Swing();
private:
	UPROPERTY()
	FTimerHandle ExecuteTimerHandle;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SkillEffect;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* CastingEffectComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SwingEffect;
};
