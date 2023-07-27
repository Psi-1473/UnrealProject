// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Third.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Third : public UMonsterSkill
{
	GENERATED_BODY()

public:
	USevarogSkill_Third();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire

	virtual void PlaySkillEffect() override;
	virtual void Attack() override;

	void PlaySwingAnim();
	

private:
	UPROPERTY(EditAnywhere)
	class UParticleSystem* CastEffect;

	UPROPERTY(EditAnywhere)
	struct FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;
};
