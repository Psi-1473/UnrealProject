// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	FString GetMontageDir(FString MontageType);

public:
	void PlayAttackMontage();
	void PlayDamagedMontage();

protected:
	UPROPERTY()
	class UAnimMontage* AttackMontage;

	UPROPERTY()
	class UAnimMontage* DamagedMontage;
};
