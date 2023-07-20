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
	virtual void PostInitializeComponents();
public:
	bool GetCanSkill() { return bCanSkill; }
	bool GetCanDash() { return bCanDash; }
	class AMyPlayer* GetTarget() { return TargetPlayer; }

	void UseSkill();
	void Dash();
	
	virtual void AttackTarget(class AMyPlayer* Target) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void Die(class AMyPlayer* Player) override;
	virtual void DestroyObject() override;

private:
	void SetCanSkillTrue();
	void SetCanDashTrue();

private:
	UPROPERTY()
	class UBossAnimInstance* AnimInst;

	UPROPERTY()
	bool bCanSkill = true;

	UPROPERTY()
	bool bCanDash = true;

	UPROPERTY()
	class AMyPlayer* TargetPlayer;

	UPROPERTY()
	FTimerHandle DashCoolTimer;

	UPROPERTY()
	FTimerHandle SkillCoolTimer;
	
};
