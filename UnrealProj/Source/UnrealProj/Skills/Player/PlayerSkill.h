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
	virtual void SetDefaultValue(); // Owner Player ���� �� �⺻ ����
public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);// ��ų ����
	virtual void PlayParticle(AActor* OwnerActor) {};// ��ų ����Ʈ (Actor ��ȯ X) ����

	virtual void CancleCast(AActor* OwnerActor); // 2�ܰ迡 ���ļ� ����ϴ� ��ų 1�ܰ迡�� ĵ��
	virtual void CastToExecute(AActor* OwnerActor) {}; // 2�ܰ迡 ���ļ� ����ϴ� ��ų 1�ܰ� -> 2�ܰ�
	virtual void SkillEnd() override; // ��ų ����� ������ �Լ�
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
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer; // ����� �÷��̾�
};
