// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void Spawn();
	void SetOwnerPlayer(class AMyPlayer* Player);
	void SetId(int num) { Id = num; }


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
	TWeakObjectPtr<class AMyPlayer> OwnerPlayer;

	UPROPERTY()
	class UVehicleStateMachine* StateMachine;
	

};
