// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerSkill.h"
#include "PlayerSkill_Sword_Third.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill_Sword_Third : public UPlayerSkill
{
	GENERATED_BODY()

public:
	UPlayerSkill_Sword_Third();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override;
	virtual void PlayParticle(AActor* OwnerActor) override;


	UPROPERTY(EditAnywhere)
	class UParticleSystem* PreParticle;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* AttackParticle;
};
