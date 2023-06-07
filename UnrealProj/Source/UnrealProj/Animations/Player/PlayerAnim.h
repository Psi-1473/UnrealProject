// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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


	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(int32 SectionIndex);

	UFUNCTION()
	void AnimNotify_Combo();

	UFUNCTION()
	void AnimNotify_AttackEnd();


public:
	UPROPERTY()
	int AttackStep = 1;

	UPROPERTY()
	bool bCombo = true;

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
	class UAnimMontage* AttackMontage;
	
};
