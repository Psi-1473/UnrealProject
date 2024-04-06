// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleStateMachine.h"

UVehicleStateMachine::UVehicleStateMachine()
{
	UVehicleNone* VehicleNone = NewObject<UVehicleNone>();
	UVehicleMount* VehicleMount = NewObject<UVehicleMount>();
	UVehicleIdle* VehicleIdle = NewObject<UVehicleIdle>();
	UVehicleMove* VehicleMove = NewObject<UVehicleMove>();
	UVehicleDismount* VehicleDismount = NewObject<UVehicleDismount>();


	AddState(VSTATE::NONE, Cast<UVehicleState>(VehicleNone));
	AddState(VSTATE::MOUNT, Cast<UVehicleState>(VehicleMount));
	AddState(VSTATE::IDLE, Cast<UVehicleState>(VehicleIdle));
	AddState(VSTATE::MOVE, Cast<UVehicleState>(VehicleMove));
	AddState(VSTATE::DISMOUNT, Cast<UVehicleState>(VehicleDismount));


	CurrentState = States[VSTATE::NONE];
}

void UVehicleStateMachine::AddState(VSTATE State, UVehicleState* StatePtr)
{
	StatePtr->StateEnum = State;
	States.Add(State, StatePtr);
}



