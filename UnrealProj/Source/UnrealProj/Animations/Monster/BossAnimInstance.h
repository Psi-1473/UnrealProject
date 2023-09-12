// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UBossAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	FString GetBossMontageDir(FString MontageType);
public:
	UFUNCTION()
		void AnimNotify_DamagedEnd();

	UFUNCTION()
		void AnimNotify_DestroyObject();

	UFUNCTION()
	void AnimNotify_SkillEnd();
	
	UFUNCTION()
	void AnimNotify_PlayEffect();

	UFUNCTION()
	void AnimNotify_HitCheck();

	UFUNCTION()
	void AnimNotify_IndicateRange();

	UFUNCTION()
	void AnimNotify_DashEnd();


public:
	void PlayStartMontage();
	void PlayDamagedMontage();
	void PlayDieMontage();
	void PlayAttackMontage();
	void PlaySkillMontage(int32 Id);
	void Dash() { bDash = true;}

private:
	void JumpToSection(UAnimMontage* Montage, int32 Section);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDeath = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bCast = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bSixthSkill = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		int SkillId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDash = false;

	UPROPERTY()
		class UAnimMontage* DamagedMontage;
	UPROPERTY()
		class UAnimMontage* AttackMontage;
	UPROPERTY()
		class UAnimMontage* SkillMontage;
	UPROPERTY()
		class UAnimMontage* StartMontage;
	UPROPERTY()
		class UAnimMontage* DieMontage;
};
