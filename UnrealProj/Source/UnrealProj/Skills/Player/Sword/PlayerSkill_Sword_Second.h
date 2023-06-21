// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Skill.h"
#include "PlayerSkill_Sword_Second.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill_Sword_Second : public USkill
{
	GENERATED_BODY()
	
public:
	UPlayerSkill_Sword_Second();

	virtual void Execute(AActor* OwnerActor) override;
	virtual void PlayParticle(AActor* OwnerActor) override;
	virtual void DestroyActor() override;

	FVector GetMoveDir() { return MoveDir; }

private:
	UPROPERTY()
	FVector MoveDir;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* PlayerParticle;
	
	UPROPERTY(EditAnywhere)
	class UParticleSystem* DestroyParticle;
};
