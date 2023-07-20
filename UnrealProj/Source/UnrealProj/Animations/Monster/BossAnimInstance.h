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

public:
	void PlayDamagedMontage();
	void PlayAttackMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool bDeath = false;

	UPROPERTY()
		class UAnimMontage* DamagedMontage;
	UPROPERTY()
		class UAnimMontage* AttackMontage;

};
