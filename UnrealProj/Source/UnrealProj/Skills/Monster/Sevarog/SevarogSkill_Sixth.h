// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Sixth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Sixth : public UMonsterSkill
{
	GENERATED_BODY()
public:
	USevarogSkill_Sixth();
	virtual void BeginPlay();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire

	virtual void PlaySkillEffect() override;

	void SpawnTornado();
	void EndSkill();
private:
	UPROPERTY()
	int Count = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;

	UPROPERTY()
	struct FTimerHandle EndTimer;

	UPROPERTY()
	struct FTimerHandle SpawnTickTimer;
};
