// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../DEFINE.h"
#include "HorseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UHorseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UHorseAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	VSTATE VehicleState;
	
};
