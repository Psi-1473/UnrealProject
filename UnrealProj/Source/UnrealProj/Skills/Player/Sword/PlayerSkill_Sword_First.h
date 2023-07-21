// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerSkill.h"
#include "PlayerSkill_Sword_First.generated.h"

/**
 * 
 */
const int MaxSpawnCount = 5;

UCLASS()
class UNREALPROJ_API UPlayerSkill_Sword_First : public UPlayerSkill
{
	GENERATED_BODY()
public:
	UPlayerSkill_Sword_First();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;
private:
	void SetParticleTimer();

private:
	

	float LocX[MaxSpawnCount] = { 120, 250, 300, 250, 120 };
	float LocY[MaxSpawnCount] = { -300, -200, 0, 200, 300 };
	float RotZ[MaxSpawnCount] = { 30, 50, 90, 130, 150 };


	
	int SpawnCount = 0;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* PlayerParticle;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;


};
