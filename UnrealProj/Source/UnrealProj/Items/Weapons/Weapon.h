// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../DEFINE.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();
	void Init(WEAPONTYPE _Type, int _Id);

	void SetMuzzleOffset(FVector Offset) { MuzzleOffset = Offset; }

	WEAPONTYPE GetType() { return Type; }
	bool GetIsRight() { return bRight; }
	class UStaticMesh* GetStaticMesh() { return StaticMesh; }
	TSubclassOf<class AProjectile> GetArrow() { return Arrow; }
	FVector GetMuzzleOffset() { return MuzzleOffset; }

private:
	WEAPONTYPE Type;

	UPROPERTY()
	int Id;

	UPROPERTY()
	bool bRight = true;

	UPROPERTY()
	class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Arrow;

	
};
