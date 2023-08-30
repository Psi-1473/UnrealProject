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

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;

private:
	void SpawnTornado();
	void DestroyTornado();
private:
	UPROPERTY()
	int Count = 0;

	UPROPERTY()
	TArray<class ASkillEffectActor*> ActorArray;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;

	UPROPERTY()
	struct FTimerHandle SpawnTickTimer;

	UPROPERTY()
	struct FTimerHandle SkillEndTimer;
};
