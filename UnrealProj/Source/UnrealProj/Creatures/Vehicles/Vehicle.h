// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../DEFINE.h"
#include "GameFramework/Character.h"
#include "Vehicle.generated.h"

UCLASS()
class UNREALPROJ_API AVehicle : public ACharacter
{
	GENERATED_BODY()
	
public:	
	AVehicle();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	void SetInfo(const class UVehicleInfo& Info);
	void SetOwnerPlayer(TWeakObjectPtr<class AMyPlayer> Player);
	void SetId(int num) { Id = num; }
	void SetIsDash(bool Value) { IsDash = Value; }

	float GetSpeed() const { return Speed; }
	float GetDashSpeed() const { return DashSpeed; }
	bool GetIsDash() const { return IsDash; }

public:
	void SetState(VSTATE State);

public:
	class UVehicleStateMachine* GetStateMachine() { return StateMachine; }

private:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY()
	int Id;

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float DashSpeed;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

	UPROPERTY()
	class UVehicleStateMachine* StateMachine;

	UPROPERTY()
	bool IsDash;
	

};
