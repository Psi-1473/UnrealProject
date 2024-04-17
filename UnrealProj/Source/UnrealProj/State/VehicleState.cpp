// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleState.h"


void UVehicleNone::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle NONE STATE"));
}

void UVehicleNone::OnUpdate()
{
}

void UVehicleNone::OnExit()
{
}


void UVehicleMount::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle MOUNT STATE"));
}

void UVehicleMount::OnUpdate()
{
}

void UVehicleMount::OnExit()
{
}


void UVehicleIdle::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle IDLE STATE"));
}

void UVehicleIdle::OnUpdate()
{
}

void UVehicleIdle::OnExit()
{
}


void UVehicleMove::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle MOVE STATE"));
}

void UVehicleMove::OnUpdate()
{
}

void UVehicleMove::OnExit()
{
}


void UVehicleDismount::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle DISMOUNT STATE"));
}

void UVehicleDismount::OnUpdate()
{
}

void UVehicleDismount::OnExit()
{
}


