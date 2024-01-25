// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnDied);

UCLASS()
class UNREALPROJ_API UMonsterAnimInstance : public UEnemyAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UFUNCTION()
	void AnimNotify_HitCheck();

	UFUNCTION()
	void AnimNotify_DamagedEnd();

	UFUNCTION()
	void AnimNotify_DestroyObject();

public:


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bDeath = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bChase = false;



public:
	FOnDied OnDied;

};
