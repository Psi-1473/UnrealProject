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

public:
	virtual void Execute(AActor* OwnerActor);
	void RegisterKey(int32 Key) { RegisteredKey = Key; }

protected:
	int32 RegisteredKey;

	bool bCanUse = true;

	UPROPERTY()
	FTimerHandle CoolDownTimer;
};
