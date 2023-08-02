// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnDied);

UCLASS()
class UNREALPROJ_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	

	FString GetMontageDir(FString MontageType);
public:
	UFUNCTION()
	void AnimNotify_HitCheck();

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
public:
	FOnDied OnDied;

};
