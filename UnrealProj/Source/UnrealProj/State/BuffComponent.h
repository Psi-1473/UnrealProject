// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UBuffComponent : public UObject
{
	GENERATED_BODY()
public:
	void Init();

	void SetDebuff(uint8 Value);
	void RemoveDebuff(uint8 Value);
	
	void UpdateDebuff();


private:
	UPROPERTY()
	uint8 DebuffFlag = 0 << 0;

	UPROPERTY()
	TMap<uint8, class UBuffState*> Debuffs;
};
