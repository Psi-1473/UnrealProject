// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DEFINE.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWeapon : public UObject
{
	GENERATED_BODY()

public:
	UWeapon();
	void Init(WEAPONTYPE _Type, int _Id);

	FString GetSocketName() { return SocketName; }
	class UStaticMesh* GetStaticMesh() { return StaticMesh; }
private:
	WEAPONTYPE Type;

	UPROPERTY()
	int Id;

	UPROPERTY()
	FString SocketName;

	UPROPERTY()
	class UStaticMesh* StaticMesh;
};
