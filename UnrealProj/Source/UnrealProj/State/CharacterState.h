// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UCharacterState : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();

	void SetMachine(class UStateMachine* M) { Machine = M; }

protected:
	UPROPERTY()
	class UStateMachine* Machine;
};

UCLASS()
class UNREALPROJ_API UIdleState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UMoveState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UJumpState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UAttackState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};