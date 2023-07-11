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
protected:
	void SetDefaultValue();
public:
	virtual void Execute(AActor* OwnerActor, bool bRangeAttack);
	virtual void PlayParticle(AActor* OwnerActor); //Attack Or Fire


	virtual void DestroyActor();
	virtual void CancleCast(AActor* OwnerActor);
	virtual void CastToExecute(AActor* OwnerActor);

	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player) { OwnerPlayer = Player; }
	
	UTexture2D* GetTexture() { return Txt; }
	int32 GetId() { return Id; }
	FString GetSkillName() { return Name; }
	bool GetIsRangeAttack() { return bRange; }

	TWeakObjectPtr<class AMyPlayer> GetOwnerPlayer() { return OwnerPlayer; }
protected:
	UPROPERTY()
	WEAPONTYPE WeaponType;

	UPROPERTY()
	bool bCanUse = true; // 지금 사용 가능한가

	UPROPERTY()
	int32 Id;// Id
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	UTexture2D* Txt;

	UPROPERTY()
	bool bRange;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASkillEffectActor> Effect; // 소환할 이펙트 액터
	
	UPROPERTY(EditAnywhere)
	ASkillEffectActor* EffectActor; // 소환된 이펙트 액터

	UPROPERTY()
	FTimerHandle CoolDownTimer; // 쿨타임 타이머

	UPROPERTY();
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer; // 사용한 플레이어
};
