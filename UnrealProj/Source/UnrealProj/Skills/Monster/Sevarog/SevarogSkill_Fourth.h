// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Fourth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Fourth : public UMonsterSkill
{
	GENERATED_BODY()
public:
	USevarogSkill_Fourth();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire

	virtual void PlaySkillEffect() override;
	virtual void Attack() override;


private:
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect2;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect3;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* AttackEffect;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* AttackEffect2;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* CastingEffectComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;
};
