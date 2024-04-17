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
	void PlayDamagedMontage();

	// Test
	void PlayRideAnim();
	void PlayDismountAnim();
	// 경직 Motage
	// 밀림 Montage;
	// 다운 Montage;
	// 날라감 상태바꾸고 날리기
	void PlaySkillMontage(int32 SkillNumber);


	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(UAnimMontage* Montage, int32 SectionIndex);

	UFUNCTION()
	void AnimNotify_Combo();
	UFUNCTION()
	void AnimNotify_FireArrow();
	UFUNCTION()
	void AnimNotify_SkillEffect();
	UFUNCTION()
	void AnimNotify_SkillEnd();
	UFUNCTION()
	void AnimNotify_DashStart();
	UFUNCTION()
	void AnimNotify_DashEnd();
	UFUNCTION()
	void AnimNotify_HitCheck();
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_SetRideIdle();
	UFUNCTION()
	void AnimNotify_SetIdle();
	UFUNCTION()
	void AnimNotify_SetRevive();
public:
	void SetBowCast(bool Value) { bBowSkillCast = Value; }
	void SetComboAndStepZero();
public:
	WEAPONTYPE WeaponType = WEAPONTYPE::WEAPON_SWORD;

	UPROPERTY()
	int AttackStep = 1;

	UPROPERTY()
	bool bCombo = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bZoom = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bBowSkillCast = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float JumpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bSprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bVehicleDash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	STATE CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	VSTATE VehicleState;
private:
	TArray<class UAnimMontage*> AttackMontages;
	TArray<class UAnimMontage*> SkillMontages;
	class UAnimMontage* RideAnim;
	class UAnimMontage* DismountAnim;
	class UAnimMontage* DamagedMontage;
	
};
