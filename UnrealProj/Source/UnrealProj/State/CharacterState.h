// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DEFINE.h"
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

	void SetState(STATE Value) { State = Value; }
	STATE GetState() { return State; }

	void SetMachine(class UStateMachine* M) { Machine = M; }

protected:
	UPROPERTY()
	class UStateMachine* Machine;

	UPROPERTY()
	STATE State;
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
UCLASS()
class UNREALPROJ_API UDamagedState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API USkillState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API USkillCastState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UPulledState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UHitAndFallState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;

private:
	float PrevVelocity;

};

UCLASS()
class UNREALPROJ_API UKnockedState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UReviveState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API ULootState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API UDeadState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API URespawnState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;

private:
	UPROPERTY()
		float SpawnTime = 3.f;
	UPROPERTY()
		float PrevTime;
};

UCLASS()
class UNREALPROJ_API UInteractState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};

UCLASS()
class UNREALPROJ_API URideState : public UCharacterState
{
	GENERATED_BODY()
public:
	virtual void OnEnter() override;
	virtual void OnUpdate() override;
	virtual void OnExit() override;
};



