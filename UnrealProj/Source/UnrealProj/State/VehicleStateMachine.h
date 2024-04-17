// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VehicleState.h"
#include "../DEFINE.h"
#include "VehicleStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UVehicleStateMachine : public UObject
{
	GENERATED_BODY()
	
public:
	UVehicleStateMachine();

	UVehicleState* GetState() { return CurrentState; }

	void SetState(VSTATE NewState)
	{
		if(CurrentState != nullptr)
			CurrentState->OnExit();
		CurrentState = States[NewState];
		CurrentState->OnEnter();
	}

	void OnUpdate()
	{
		CurrentState->OnUpdate();
	}

	void AddState(VSTATE State, UVehicleState* StatePtr);

private:

	UPROPERTY()
	UVehicleState* CurrentState;

	UPROPERTY()
	TMap<VSTATE, UVehicleState*> States;
};
