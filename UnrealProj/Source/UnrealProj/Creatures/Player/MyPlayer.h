// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../DEFINE.h"
#include "MyPlayer.generated.h"

UCLASS()
class UNREALPROJ_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayer();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class UPlayerAnim* GetAnimInst() { return AnimInst; }
	class UCharacterState* GetState();
	class UCharacterState* GetSpecificState(STATE Value);


	void SetState(STATE Value);

private:
	void EquipWeapon(class UWeapon* _Weapon);

	void SetDefaultCamera();
	void SetAnimByWeapon(WEAPONTYPE Type);

private:
	UPROPERTY(EditAnywhere)
	class UWeapon* EquipedWeapon;

private:
	UPROPERTY(EditAnywhere)
	class UStateMachine* StateMachine;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UAnimInstance>> AnimClasses;

	UPROPERTY(EditAnywhere)
	class UPlayerAnim* AnimInst;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Weapon;
};
