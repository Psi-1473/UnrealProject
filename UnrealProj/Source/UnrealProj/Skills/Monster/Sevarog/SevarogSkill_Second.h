// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Second.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Second : public UMonsterSkill
{
	GENERATED_BODY()
	
public:
	USevarogSkill_Second();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire
	virtual void IndicateRange() override;

	virtual void PlaySkillEffect() override;
	virtual void Attack() override;
	void HitCheck();
private:
	UPROPERTY(EditAnywhere)
	FVector TargetPos;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect2;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* FireEffect;

	UPROPERTY(EditAnywhere)
	struct FTimerHandle HitCheckTimerHandle;

};
