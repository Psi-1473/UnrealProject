// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "BossMonster.generated.h"

UENUM(BlueprintType)
 enum class SevarogCastType : uint8
 {
	 CAST_SWING,
	 
	 CAST_NONE
 };
UCLASS()
class UNREALPROJ_API ABossMonster : public AMonster
{
	GENERATED_BODY()

public:
	ABossMonster();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents();
public:
	void SetCastSkill(bool Value) { bCastSkill = Value; }
	void SetSixthSkill(bool Value) { bSixthSkill = Value; }
	void SetExecutingSkill(class UMonsterSkill* NewSkill) { ExecutingSkill = NewSkill; }
	void SetDashEffectVisibility(bool Value);

	bool GetCanSkill() { return bCanSkill; }
	bool GetCanDash() { return bCanDash; }
	bool GetCastSkill() { return bCastSkill; }
	bool GetSixthSkill() { return bSixthSkill; }
	class UMonsterSkill* GetExecutingSkill() { return ExecutingSkill; }
	class AMyPlayer* GetTarget() { return TargetPlayer; }
	class UBossAnimInstance* GetAnimInst() { return AnimInst; }


	virtual void AttackTarget() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void Die(class AMyPlayer* Player) override;
	virtual void DestroyObject() override;

	void UseSkill();
	class UMonsterSkill* SelectSkill();
	void Dash();
	void StartCooldown();
private:
	void SetCanSkillTrue();
	void SetCanDashTrue();

private:
	UPROPERTY()
	class UBossAnimInstance* AnimInst;

	UPROPERTY()
	bool bCanSkill = false;

	UPROPERTY()
	bool bCanDash = false;

	UPROPERTY()
	bool bCastSkill = false;

	UPROPERTY()
	bool bSixthSkill = false;

	UPROPERTY()
	class UMonsterSkill* ExecutingSkill;
	//�뵵 - ĳ���� �� ����ϴ� ��ų�� ���� ��, 
	// bCastSkill�� ���� Cast �ִϸ��̼� ����
	// � Cast �ִϸ��̼��� ������ ���� ExecutingSkill�� Id�� ���ؼ� ����

	UPROPERTY()
	class AMyPlayer* TargetPlayer;

	UPROPERTY()
	FTimerHandle DashCoolTimer;

	UPROPERTY()
	FTimerHandle SkillCoolTimer;

	UPROPERTY()
	TArray<class UMonsterSkill*> SkillList;

	UPROPERTY()
	struct FTimerHandle RangeToAttackTimer;

	UPROPERTY()
	int RangeCount = 0;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* DashParticleComp;
	
};
