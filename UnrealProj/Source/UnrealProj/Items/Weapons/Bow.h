// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ABow : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void OnLeftMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseReleased(class AMyPlayer* Player) override;
	
	bool GetZoom() { return bZoom; }

private:
	void ZoomIn(class AMyPlayer* Player);
	void ZoomOut(class AMyPlayer* Player);

private:
	UPROPERTY()
	bool CameraMoved = false;

	UPROPERTY()
	bool bZoom = false;

};
