// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../DEFINE.h"
#include "../Item.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

	void SetMuzzleOffset(FVector Offset) { MuzzleOffset = Offset; }

	WEAPONTYPE GetType() { return Type; }
	bool GetIsRight() { return bRight; }
	FVector GetMuzzleOffset() { return MuzzleOffset; }
	TSubclassOf<class AProjectile> GetArrow() { return Arrow; }

public:
	virtual void UseItem() override;
	virtual void SetItemMesh(int _Id, WEAPONTYPE _Type = WEAPON_END) override;

	virtual FRichImageRow* GetItemImage(class UMyGameInstance* GInstance) override;
private:
	WEAPONTYPE Type;

	UPROPERTY()
	bool bRight = true;



	UPROPERTY(EditAnywhere)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Arrow;

	
};
