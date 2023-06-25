// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DEFINE.h"
#include "Skill.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USkill : public UObject
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);
	virtual void PlayParticle(AActor* OwnerActor);
	virtual void DestroyActor();
	virtual void CancleCast(AActor* OwnerActor);
	virtual void CastToExecute(AActor* OwnerActor);

	int32 GetId() { return Id; }
	bool GetIsRangeAttack() { return bRange; }
protected:
	WEAPONTYPE WeaponType;

	UPROPERTY()
	bool bCanUse = true; // ���� ��� �����Ѱ�

	UPROPERTY()
	int32 Id; // Id
	
	UPROPERTY()
	bool bRange;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillEffectActor> Effect; // ��ȯ�� ����Ʈ ����
	
	UPROPERTY(EditAnywhere)
	ASkillEffectActor* EffectActor; // ��ȯ�� ����Ʈ ����

	UPROPERTY()
	FTimerHandle CoolDownTimer; // ��Ÿ�� Ÿ�̸�

	UPROPERTY();
	class AMyPlayer* OwnerPlayer; // ����� �÷��̾�
};
