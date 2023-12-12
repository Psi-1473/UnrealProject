// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASword : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void OnLeftMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseClicked(class AMyPlayer* Player) override;
};
