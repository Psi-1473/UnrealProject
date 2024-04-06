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
	void AddNewVehicle(class AVehicle* NewVehicle);
	void RemoveVehicle(class AVehicle* OldVehicle);

	void RegisterVehicle(class AVehicle* Vehicle);
	void RideVehicle();
	void Dismount();

public:
	class AVehicle* GetCurrentVehicle() { return VehicleInUse; }
	bool GetIsRiding() { return IsRiding; }

	void SetIsRiding(bool Value)  { IsRiding = Value; }

private:

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

	

	UPROPERTY()
	TArray<class AVehicle*> Vehicles;

	UPROPERTY()
	class AVehicle* VehicleInUse;

	UPROPERTY()
	bool IsRiding = false;
		
};
