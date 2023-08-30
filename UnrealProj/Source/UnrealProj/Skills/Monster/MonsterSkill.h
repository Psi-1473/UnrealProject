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
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack); // 스킬 시작
	virtual void IndicateRange() {}; // 히트 범위 표시
	virtual void Update() {}; // 스킬 객체 Update 함수
	virtual void AttackOrSpawnSkillActor() {}; // Hit체크, 스킬 액터 소환
	virtual void PlaySkillEffect() {}; // AnimNotify를 통해 스킬 이펙트만 실행시킬 때
	virtual void PlayParticle(AActor* OwnerActor) {}; // Execute등 코드에서 바로 이펙트 실행 시킬 때
	
	virtual void SkillEnd(); // 스킬 종료시 실행할 함수

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
