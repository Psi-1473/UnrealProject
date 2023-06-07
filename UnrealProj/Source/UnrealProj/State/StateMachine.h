// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.h"
#include "../DEFINE.h"
#include "StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UStateMachine : public UObject
{
	GENERATED_BODY()
public:
	UStateMachine();
public:
	UCharacterState* GetState() { return State; }
	UCharacterState* GetState(STATE Value) { return States[Value]; }

	class AMyPlayer* GetOwner() { return OwnerCreature; }

	void SetState(STATE StateValue) {
		State->OnExit();
		State = States[StateValue];
		State->OnEnter();
	};

	void SetOwner(class AMyPlayer* Owner) { OwnerCreature = Owner; }

	void OnUpdate();
public:
	void SetOwnerCreature(class AMyPlayer* Creature) { OwnerCreature = Creature; }

private:
	UPROPERTY()
	UCharacterState* State;

	UPROPERTY()
	TMap<STATE, UCharacterState*> States;

	UPROPERTY()
	class AMyPlayer* OwnerCreature;

	
};
