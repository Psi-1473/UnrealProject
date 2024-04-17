// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VehicleInfo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UVehicleInfo : public UObject
{
	GENERATED_BODY()

public:
	void Init(int VehicleId, TWeakObjectPtr<class AMyPlayer> Player);

	float GetSpeed() const { return Speed; }
	float GetDashSpeed() const { return DashSpeed; }
	FString GetVehicleName() const { return Name; }
	int GetId() const { return Id; }


	FString GetDir() { return Dir; }

private:
	UPROPERTY()
	float DashSpeed = 0.0f;
	UPROPERTY()
	float Speed = 0.0f;

	UPROPERTY()
	int Id;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Explanation;

	UPROPERTY()
	FString Dir;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;
	
};
