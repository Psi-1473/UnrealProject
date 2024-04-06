// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DEFINE.h"
#include "UObject/NoExportTypes.h"
#include "VehicleState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UVehicleState : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void OnEnter() {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

	VSTATE StateEnum;
};
UCLASS()
class UNREALPROJ_API UVehicleNone : public UVehicleState
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};

UCLASS()
class UNREALPROJ_API UVehicleMount : public UVehicleState
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};


UCLASS()
class UNREALPROJ_API UVehicleIdle : public UVehicleState
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};

UCLASS()
class UNREALPROJ_API UVehicleMove : public UVehicleState
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};


UCLASS()
class UNREALPROJ_API UVehicleDismount : public UVehicleState
{
	GENERATED_BODY()

public:
	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
};