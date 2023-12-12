// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.h"
#include "WeaponState.h"
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
	class AMyPlayer* GetOwner() { return OwnerCreature; }

	UCharacterState* GetState() { return State; }
	UCharacterState* GetState(STATE Value) { return States[Value]; }
	UWeaponState* GetWeaponState() { return WeaponState; }
	UWeaponState* GetState(WEAPONTYPE Value) { return WeaponStates[Value]; }
	
	void SetState(STATE StateValue) {
		State->OnExit();
		State = States[StateValue];
		State->OnEnter();
	};

	void SetWeaponState(WEAPONTYPE StateValue) { WeaponState = WeaponStates[StateValue]; }

	


	void SetOwner(class AMyPlayer* Owner) { OwnerCreature = Owner; }

	void OnUpdate();
	void InitCharacterState();
	void InitWeaponState();
	void AddState(STATE StateValue, UCharacterState* StatePtr);
public:
	void SetOwnerCreature(class AMyPlayer* Creature) { OwnerCreature = Creature; }

private:
	UPROPERTY()
	UCharacterState* State;
	UPROPERTY()
	UWeaponState* WeaponState;

	UPROPERTY()
	TMap<STATE, UCharacterState*> States;
	UPROPERTY()
	TMap<WEAPONTYPE, UWeaponState*> WeaponStates;


	UPROPERTY()
	class AMyPlayer* OwnerCreature;

	
};
