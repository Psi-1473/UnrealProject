// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWeaponState : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void OnLeftMouseClicked(class AMyPlayer* Player);
	virtual void OnRightMouseClicked(class AMyPlayer* Player) {};
	virtual void OnRightMouseReleased(class AMyPlayer* Player) {};
	virtual void OnUpdate() {};

	void SetMachine(class UStateMachine* NewMachine) { Machine = NewMachine;}
protected:
	UPROPERTY()
	class UStateMachine* Machine;
};

UCLASS()
class UNREALPROJ_API USwordState : public UWeaponState
{
	GENERATED_BODY()

public:
	virtual void OnLeftMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseReleased(class AMyPlayer* Player) override;
	virtual void OnUpdate() override;
};

UCLASS()
class UNREALPROJ_API UBowState : public UWeaponState
{
	GENERATED_BODY()

public:
	virtual void OnLeftMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseClicked(class AMyPlayer* Player) override;
	virtual void OnRightMouseReleased(class AMyPlayer* Player) override;
	virtual void OnUpdate() override;
	void Fire();

	bool GetZoom() { return bZoom; };
	
private:
	void ZoomIn(class AMyPlayer* Player);
	void ZoomOut(class AMyPlayer* Player);
	void FindTarget();
	
	void FireArrow(FVector DestPos);
	FVector GetViewportToWorld(class APlayerController* Controller);
	FVector GetArrowDir(FVector Start, FVector Dir);

private:
	UPROPERTY()
	bool bArrowTarget = false;

	UPROPERTY()
	bool CameraMoved = false;

	UPROPERTY()
	bool bZoom = false;


	UPROPERTY()
	class AActor* Target = nullptr;
};

