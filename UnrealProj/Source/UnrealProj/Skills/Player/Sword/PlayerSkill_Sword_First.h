// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Skill.h"
#include "PlayerSkill_Sword_First.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UPlayerSkill_Sword_First : public USkill
{
	GENERATED_BODY()

	virtual void Execute(AActor* OwnerActor) override;
};
