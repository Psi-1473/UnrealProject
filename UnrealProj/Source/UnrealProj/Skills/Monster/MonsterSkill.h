// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Skill.h"
#include "MonsterSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UMonsterSkill : public USkill
{
	GENERATED_BODY()
	
public:
	bool GetCanUse() { return bCanUse; }

	void SetCanUse(bool Value) { bCanUse = Value; }
	void SetOwnerMonster(TWeakObjectPtr<class AMonster> Monster) { OwnerMonster = Monster; }

public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack); // ��ų ����
	virtual void IndicateRange() {}; // ��Ʈ ���� ǥ��
	virtual void Update() {}; // ��ų ��ü Update �Լ�
	virtual void AttackOrSpawnSkillActor() {}; // Hitüũ, ��ų ���� ��ȯ
	virtual void PlaySkillEffect() {}; // AnimNotify�� ���� ��ų ����Ʈ�� �����ų ��
	virtual void PlayParticle(AActor* OwnerActor) {}; // Execute�� �ڵ忡�� �ٷ� ����Ʈ ���� ��ų ��
	
	virtual void SkillEnd(); // ��ų ����� ������ �Լ�

	void EndCoolDown();

protected:
	bool IsTargetInCircleRange(AActor* HitActor, AActor* TargetActor, float RadialAngle = 360.f);
protected:
	UPROPERTY()
	TWeakObjectPtr<class AMonster> OwnerMonster;

	UPROPERTY()
	struct FTimerHandle CoolTimeHandler;

	UPROPERTY();
	float CoolTime;

	UPROPERTY()
	float RangeSize;

	UPROPERTY()
	float RangeAngle;
};
