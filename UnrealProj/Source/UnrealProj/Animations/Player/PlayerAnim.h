// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../DEFINE.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlaySkillMontage(int32 SkillNumber);



	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(UAnimMontage* Montage, int32 SectionIndex);

	UFUNCTION()
	void AnimNotify_Combo();
	UFUNCTION()
	void AnimNotify_FireArrow();
	UFUNCTION()
	void AnimNotify_HitCheck();
	UFUNCTION()
	void AnimNotify_AttackEnd();


public:
	WEAPONTYPE WeaponType = WEAPON_SWORD;

	UPROPERTY()
	int AttackStep = 1;

	UPROPERTY()
	bool bCombo = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bZoom = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float JumpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bSprint;

private:
	TArray<class UAnimMontage*> AttackMontages;
	TArray<class UAnimMontage*> SkillMontages;
	
};
