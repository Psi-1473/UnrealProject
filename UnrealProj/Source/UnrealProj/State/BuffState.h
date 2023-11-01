// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffState.generated.h"

/**
 *
 */
UCLASS()
class UNREALPROJ_API UBuffState : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};

UCLASS()
class UNREALPROJ_API UBurnState : public UBuffState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UPoisonState : public UBuffState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};
