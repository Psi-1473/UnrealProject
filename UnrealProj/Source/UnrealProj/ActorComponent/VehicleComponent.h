// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VehicleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UVehicleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVehicleComponent();


	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player);
	void AddNewVehicle(class UVehicleInfo* NewVehicle);
	void RemoveVehicle(class UVehicleInfo* OldVehicle);

	void RegisterVehicle(class UVehicleInfo* Vehicle);
	void RideVehicle();

	void SpawnVehicle();
	void DespawnVehicle();


public:
	class UVehicleInfo* GetRegisteredVehicleInfo() { return RegisteredVehicle; }
	class AVehicle* GetCurrentVehicle() { return VehicleInUse; }
	bool GetIsRiding() { return IsRiding; }

	void SetIsRiding(bool Value)  { IsRiding = Value; }
	void SetVehicleInUse(class AVehicle* Vehicle) { VehicleInUse = Vehicle; }

public:
	void StartDash();
	void EndDash();

private:

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

	

	UPROPERTY()
	TArray<class UVehicleInfo*> Vehicles;

	UPROPERTY()
	class UVehicleInfo* RegisteredVehicle;

	UPROPERTY()
	class AVehicle* VehicleInUse;

	UPROPERTY()
	bool IsRiding = false;
		
};
