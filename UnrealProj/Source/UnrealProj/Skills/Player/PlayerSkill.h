// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Skill.h"
#include "PlayerSkill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill : public USkill
{
	GENERATED_BODY()
protected:
	virtual void SetDefaultValue(); // Owner Player 설정 및 기본 세팅
public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);// 스킬 실행
	virtual void PlayParticle(AActor* OwnerActor) {};// 스킬 이펙트 (Actor 소환 X) 실행

	virtual void CancleCast(AActor* OwnerActor); // 2단계에 걸쳐서 사용하는 스킬 1단계에서 캔슬
	virtual void CastToExecute(AActor* OwnerActor) {}; // 2단계에 걸쳐서 사용하는 스킬 1단계 -> 2단계
	virtual void SkillEnd() override; // 스킬 종료시 실행할 함수
	void InitSkillValue(class AMyPlayer* Player);


	void DecreaseCoolDown(float DeltaSeconds);
public:
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }

	WEAPONTYPE GetWeaponType() { return WeaponType; }
	TWeakObjectPtr<class AMyPlayer> GetOwnerPlayer() { return OwnerPlayer; }
private:
	int32 GetIdByName(FString Str);
	void SetWeaponType(FString Str);
protected:
	UPROPERTY()
	WEAPONTYPE WeaponType;

	UPROPERTY();
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer; // 사용한 플레이어
};
