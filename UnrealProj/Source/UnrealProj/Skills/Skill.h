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
	USkill();
protected:
	virtual void SetDefaultValue() {};
public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);
	virtual void IndicateRange() {}; // ��Ʈ ���� ǥ��
	virtual void Update() {}; // ��ų ��ü Update �Լ�
	virtual void AttackOrSpawnSkillActor() {}; // Hitüũ, ��ų ���� ��ȯ
	virtual void PlaySkillEffect() {}; // AnimNotify�� ���� ��ų ����Ʈ�� �����ų ��
	virtual void PlayParticle(AActor* OwnerActor) {}; //Attack Or Fire
	virtual void DestroyActor();
	
public:
	virtual void SkillEnd(); // ��ų ����� ������ �Լ�

	UTexture2D* GetTexture() { return Txt; }
	int32 GetId() { return Id; }
	FString GetSkillName() { return Name; }
	FString GetExplanation() { return Explanation; }
	bool GetIsRangeAttack() { return bRange; }
	float GetMp() { return Mp; }
	float GetRemainingTime(){ return RemainingTime;}
	float GetCooldownRatio() { return RemainingTime / (float)CoolDown; }

protected:
	void PlaySoundAtLocation(UWorld* Wolrd, FVector Location, class USoundBase* Sound);

protected:
	UPROPERTY()
	bool bCanUse = true;

	/*
	 Data Values
	*/
	UPROPERTY()
	int CoolDown;
	UPROPERTY()
	int32 Id;// Id
	UPROPERTY()
	FString Name;
	UPROPERTY()
	FString Explanation;
	UPROPERTY()
	int32 Mp;

	UPROPERTY()
	float RemainingTime = 0.f;

	UPROPERTY()
	UTexture2D* Txt;

	UPROPERTY()
	bool bRange;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillEffectActor> Effect; // ��ȯ�� ����Ʈ ����
	
	UPROPERTY(EditAnywhere)
	ASkillEffectActor* EffectActor; // ��ȯ�� ����Ʈ ����

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillRangeActor> SkillRangeActor;

	UPROPERTY()
	class USoundWave* HitSound;

	UPROPERTY()
	class UParticleSystem* HitEffect;

	UPROPERTY()
	struct FTimerHandle CooldownTimer;


};
