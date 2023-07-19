// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ABossMonster : public AMonster
{
	GENERATED_BODY()

public:
	ABossMonster();

	virtual void BeginPlay() override;
public:
	bool GetCanSkill() { return bCanSkill; }
	bool GetCanDash() { return bCanDash; }
	class AMyPlayer* GetTarget() { return Target; }

	void UseSkill();
	void Dash();
	

private:
	void SetCanSkillTrue();
	void SetCanDashTrue();

private:
	UPROPERTY()
	bool bCanSkill = true;

	UPROPERTY()
	bool bCanDash = true;

	UPROPERTY()
	class AMyPlayer* Target;

	UPROPERTY()
	FTimerHandle DashCoolTimer;

	UPROPERTY()
	FTimerHandle SkillCoolTimer;
	
};
