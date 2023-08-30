// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSkill.h"
#include "SevarogSkill_Fifth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USevarogSkill_Fifth : public UMonsterSkill
{
	GENERATED_BODY()
	
public:
	USevarogSkill_Fifth();

	virtual void Execute(AActor* OwnerActor, bool bRangeAttack) override; // ��ų ����
	virtual void AttackOrSpawnSkillActor() override; // Hitüũ, ��ų ���� ��ȯ

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> FireProjectile;
};
